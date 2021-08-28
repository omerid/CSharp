#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifndef HTTP_PARSER
#define HTTP_PARSER

#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <map>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

struct SocketState
{
	SOCKET id;			// Socket handle
	int	recv;			// Receiving?
	int	send;			// Sending?
	int sendSubType;	// Sending sub-type
	char buffer[1024];
	int len;
};

const int TIME_PORT = 27015;
const int MAX_SOCKETS = 60;
const int EMPTY = 0;
const int LISTEN = 1;
const int RECEIVE = 2;
const int IDLE = 3;
const int SEND = 4;
const int GET = 5;
const int POST = 6;
const int PUT = 7;
const int OPTIONS = 8;
const int TRACE = 9;
const int HEAD = 10;
const int _DELETE = 11;
const int EXIT = 12;
const int ERROR_REQUEST = 13;


bool addSocket(SOCKET id, int what);
void removeSocket(int index);
void acceptConnection(int index);
void receiveMessage(int index);
void sendMessage(int index);
void parseHttpRequest(char* recvBuff, string& req);
string getAnswer(string request);
string putAnswer(string req, char* requestContent);
string deleteAnswer(string request);
string optionsAnswer();
string traceAnswer(char* requestContent);
string headAnswer(string request);
string postAnswer(string req, char* requestContent);
string getFileName(string request);
string getFileContent(string request);
string writeToFile(string fileName, string content);
string deleteFile(string fileName);
string headerToSend();
string createOpeningHeader(const string &body);
string getSizeOfBodyMessage(const string& body);
void findMethodOfHttpRequest(string &recvReq, int &subType);
void stringQuery(string path, string* fileName, string* langParam);

struct SocketState sockets[MAX_SOCKETS] = { 0 };
int socketsCount = 0;
struct timeval timeout;

void main()
{
	// Initialize Winsock (Windows Sockets).
	// Create a WSADATA object called wsaData.
	// The WSADATA structure contains information about the Windows 
	// Sockets implementation.
	WSAData wsaData;

	// Call WSAStartup and return its value as an integer and check for errors.
	// The WSAStartup function initiates the use of WS2_32.DLL by a process.
	// First parameter is the version number 2.2.
	// The WSACleanup function destructs the use of WS2_32.DLL by a process.
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Server: Error at WSAStartup()\n";
		return;
	}

	// Server side:
	// Create and bind a socket to an internet address.
	// Listen through the socket for incoming connections.
	// After initialization, a SOCKET object is ready to be instantiated.
	// Create a SOCKET object called listenSocket. 
	// For this application:	use the Internet address family (AF_INET), 
	//							streaming sockets (SOCK_STREAM), 
	//							and the TCP/IP protocol (IPPROTO_TCP).
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Check for errors to ensure that the socket is a valid socket.
	// Error detection is a key part of successful networking code. 
	// If the socket call fails, it returns INVALID_SOCKET. 
	// The if statement in the previous code is used to catch any errors that
	// may have occurred while creating the socket. WSAGetLastError returns an 
	// error number associated with the last error that occurred.
	if (INVALID_SOCKET == listenSocket)
	{
		cout << "Time Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// For a server to communicate on a network, it must bind the socket to 
	// a network address.
	// Need to assemble the required data for connection in sockaddr structure.
	// Create a sockaddr_in object called serverService. 
	sockaddr_in serverService;
	// Address family (must be AF_INET - Internet address family).
	serverService.sin_family = AF_INET;
	// IP address. The sin_addr is a union (s_addr is a unsigned long 
	// (4 bytes) data type).
	// inet_addr (Iternet address) is used to convert a string (char *) 
	// into unsigned long.
	// The IP address is INADDR_ANY to accept connections on all interfaces.
	serverService.sin_addr.s_addr = INADDR_ANY;
	// IP Port. The htons (host to network - short) function converts an
	// unsigned short from host to TCP/IP network byte order 
	// (which is big-endian).
	serverService.sin_port = htons(TIME_PORT);

	// Bind the socket for client's requests.

	// The bind function establishes a connection to a specified socket.
	// The function uses the socket handler, the sockaddr structure (which
	// defines properties of the desired connection) and the length of the
	// sockaddr structure (in bytes).
	if (SOCKET_ERROR == bind(listenSocket, (SOCKADDR *)&serverService, sizeof(serverService)))
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(listenSocket);
		WSACleanup();
		return;
	}

	// Listen on the Socket for incoming connections.
	// This socket accepts only one connection (no pending connections 
	// from other clients). This sets the backlog parameter.
	if (SOCKET_ERROR == listen(listenSocket, 5))
	{
		cout << "Time Server: Error at listen(): " << WSAGetLastError() << endl;
		closesocket(listenSocket);
		WSACleanup();
		return;
	}
	addSocket(listenSocket, LISTEN);

	// Accept connections and handles them one by one.
	while (true)
	{
		// The select function determines the status of one or more sockets,
		// waiting if necessary, to perform asynchronous I/O. Use fd_sets for
		// sets of handles for reading, writing and exceptions. select gets "timeout" for waiting
		// and still performing other operations (Use NULL for blocking). Finally,
		// select returns the number of descriptors which are ready for use (use FD_ISSET
		// macro to check which descriptor in each set is ready to be used).
		fd_set waitRecv;
		FD_ZERO(&waitRecv);
		for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if ((sockets[i].recv == LISTEN) || (sockets[i].recv == RECEIVE))
				FD_SET(sockets[i].id, &waitRecv);
		}

		fd_set waitSend;
		FD_ZERO(&waitSend);
		for (int i = 0; i < MAX_SOCKETS; i++)
		{
			if (sockets[i].send == SEND)
				FD_SET(sockets[i].id, &waitSend);
		}

		// Wait for interesting event.
		// Note: First argument is ignored. The fourth is for exceptions.
		// And as written above the last is a timeout, hence we are blocked if nothing happens.

		int nfd;
		nfd = select(0, &waitRecv, &waitSend, NULL, NULL);
		if (nfd == SOCKET_ERROR)
		{
			cout << "Time Server: Error at select(): " << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		for (int i = 0; i < MAX_SOCKETS && nfd > 0; i++)
		{
			if (FD_ISSET(sockets[i].id, &waitRecv))
			{
				nfd--;
				switch (sockets[i].recv)
				{
				case LISTEN:
					acceptConnection(i);
					break;

				case RECEIVE:
					receiveMessage(i);
					break;
				}
			}
		}

		for (int i = 0; i < MAX_SOCKETS && nfd > 0; i++)
		{
			if (FD_ISSET(sockets[i].id, &waitSend))
			{
				nfd--;
				switch (sockets[i].send)
				{
				case SEND:
					sendMessage(i);
					break;
				}
			}
		}
	}

	// Closing connections and Winsock.
	cout << "Time Server: Closing Connection.\n";
	closesocket(listenSocket);
	WSACleanup();
}

bool addSocket(SOCKET id, int what)
{
	unsigned long flag = 1;
	if (ioctlsocket(id, FIONBIO, &flag) != 0)
	{
		cout << "Time Server: Error at ioctlsocket(): " << WSAGetLastError() << endl;
	}
	for (int i = 0; i < MAX_SOCKETS; i++)
	{
		if (sockets[i].recv == EMPTY)
		{
			sockets[i].id = id;
			sockets[i].recv = what;
			sockets[i].send = IDLE;
			sockets[i].len = 0;
			socketsCount++;
			if (setsockopt(id, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
			{
				cout << "Time Server: Error at setsockopt: " << WSAGetLastError() << endl;
				return false;
			}
			return true;
		}
	}
	return false;
}

void removeSocket(int index)
{
	sockets[index].recv = EMPTY;
	sockets[index].send = EMPTY;
	socketsCount--;
}

void acceptConnection(int index)
{
	SOCKET id = sockets[index].id;
	struct sockaddr_in from;		// Address of sending partner
	int fromLen = sizeof(from);

	SOCKET msgSocket = accept(id, (struct sockaddr *)&from, &fromLen);
	if (INVALID_SOCKET == msgSocket)
	{
		cout << "Time Server: Error at accept(): " << WSAGetLastError() << endl;
		return;
	}
	cout << "Time Server: Client " << inet_ntoa(from.sin_addr) << ":" << ntohs(from.sin_port) << " is connected." << endl;

	//
	// Set the socket to be in non-blocking mode.
	//
	unsigned long flag = 1;
	if (ioctlsocket(msgSocket, FIONBIO, &flag) != 0)
	{
		cout << "Time Server: Error at ioctlsocket(): " << WSAGetLastError() << endl;
	}

	if (addSocket(msgSocket, RECEIVE) == false)
	{
		cout << "\t\tToo many connections, dropped!\n";
		closesocket(id);
	}
	return;
}

void receiveMessage(int index)
{
	SOCKET msgSocket = sockets[index].id;

	int len = sockets[index].len;
	int bytesRecv = recv(msgSocket, &sockets[index].buffer[len], sizeof(sockets[index].buffer) - len, 0);

	if (SOCKET_ERROR == bytesRecv)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
		{
			cout << "Time Server: Error at recv(): Too long to receive, time out triggered." << endl;
		}
		else
		{
			cout << "Time Server: Error at recv(): " << WSAGetLastError() << endl;
		}
		closesocket(msgSocket);
		removeSocket(index);
		return;
	}
	if (bytesRecv == 0)
	{
		closesocket(msgSocket);
		removeSocket(index);
		return;
	}
	else
	{
		sockets[index].buffer[len + bytesRecv] = '\0'; //add the null-terminating to make it a string
		cout << "Time Server: Recieved: " << bytesRecv << " bytes of \"" << &sockets[index].buffer[len] << "\" message.\n";

		sockets[index].len += bytesRecv;
		string req;

		if (sockets[index].len > 0)
		{
			parseHttpRequest(sockets[index].buffer, req);
			sockets[index].len = 0;
			sockets[index].send = SEND;

			string answer;

			findMethodOfHttpRequest(req, sockets[index].sendSubType);

			if (sockets[index].sendSubType == EXIT)
			{
				closesocket(msgSocket);
				removeSocket(index);
				return;
			}
			else
			{
				if (sockets[index].sendSubType == GET)
				{
					answer = getAnswer(req);
				}

				else if (sockets[index].sendSubType == PUT)
				{
					answer = putAnswer(req, sockets[index].buffer);
				}

				else if (sockets[index].sendSubType == _DELETE)
				{
					answer = deleteAnswer(req);
				}

				else if (sockets[index].sendSubType == OPTIONS)
				{
					answer = optionsAnswer();
				}

				else if (sockets[index].sendSubType == HEAD)
				{
					answer = headAnswer(req);
				}

				else if (sockets[index].sendSubType == TRACE)
				{
					answer = traceAnswer(sockets[index].buffer);
				}

				else if (sockets[index].sendSubType == POST)
				{
					answer = postAnswer(req, sockets[index].buffer);
				}

				else
				{
					answer = req + " method not supported.";
				}
			}


			for (int i = 0; i < answer.size(); ++i)
			{
				sockets[index].buffer[i] = answer[i];
			}

			sockets[index].buffer[answer.size()] = 0;
			return;
		}
	}
}

void sendMessage(int index)
{
	int bytesSent = 0;
	char sendBuff[255];
	SOCKET msgSocket = sockets[index].id;

	strcpy(sendBuff, sockets[index].buffer);
	bytesSent = send(msgSocket, sendBuff, (int)strlen(sendBuff), 0);
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Server: Error at send(): " << WSAGetLastError() << endl;
		return;
	}

	cout << "Time Server: Sent: " << bytesSent << "\\" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	sockets[index].send = IDLE;
}

string getAnswer(string request)
{
	string body = getFileContent(request);
	string messageStatus = createOpeningHeader(body);
	messageStatus += headerToSend();
	messageStatus += getSizeOfBodyMessage(body);

	return messageStatus + "\r\n\n" + body;
}

string optionsAnswer()
{
	string returnMessage = "HTTP/1.1 200 OK\r\n";
	returnMessage += headerToSend();
	returnMessage += "0\r\nAllowed methods: GET, PUT, OPTIONS, TRACE, HEAD, DELETE, POST, Exit\r\n\n";
	return returnMessage;
}

string putAnswer(string req, char* requestContent)
{
	string fileName = getFileName(req);
	string content(requestContent);
	int length = content.length();

	string body = content.substr(content.find("\n\r\n") + 3, content.length());

	string answer = writeToFile(fileName, body);
	answer += headerToSend();

	if (answer.find("201") != string::npos)
	{
		answer += getSizeOfBodyMessage(body);
		answer += "\r\n\n";
		answer += body;
	}
	else
	{
		answer += "0\r\n\n";
	}

	return answer;
}

string deleteAnswer(string request)
{
	string fileName = getFileName(request);
	string deleteAnswer = deleteFile(fileName);
	deleteAnswer += headerToSend();

	string body;

	if (deleteAnswer.find("200") != string::npos)
		body = "<html><h1>URL deleted.</h1></html>";
	else
		body = "<html><h1>URL not deleted.</h1></html>";

	deleteAnswer += getSizeOfBodyMessage(body) += "\r\n\n" + body;;

	return deleteAnswer;
}

string headAnswer(string request)
{
	string body = getFileContent(request);
	string messageStatus = createOpeningHeader(body);

	messageStatus += headerToSend();

	return messageStatus + "0\r\n\n";
}

string traceAnswer(char* requestContent)
{
	string returnMessage = "HTTP/1.1 200 OK\r\n";
	returnMessage += headerToSend();
	string content(requestContent);
	returnMessage += getSizeOfBodyMessage(content) + "\r\n\n" + content;
	return returnMessage;
}


string postAnswer(string req, char* requestContent)
{
	string fileName = getFileName(req);
	cout << "-------------------------------------- " << endl;
	cout << "POST Request: " << fileName << endl;
	cout << "-------------------------------------- " << endl;
	string answer = "HTTP/1.1 200 OK\r\n";;
	answer += headerToSend();
	answer += "0\r\n\n";
	
	return answer;
}

string getFileName(string request)
{
	request = request.substr(request.find(' ') + 1, request.size());
	string fileName = request.substr(1, request.find(' '));
	fileName[fileName.length() - 1] = '\0';
	return fileName;
}


string getFileContent(string request)
{
	string path = getFileName(request);
	string fileName = " ";
	string langParam = " ";
	string html = ".html\0";
	stringQuery(path, &fileName, &langParam);

	if (langParam != " ")
	{
		fileName = fileName.substr(0, fileName.find('.'));
		fileName += ("-" + langParam);
		fileName = fileName.substr(0, fileName.find('-')+3);
		fileName += html;
	}
	string content;
	if (fileName.size() > 0)
	{
		ifstream file;
		file.open(fileName);
		if (file.fail())
			return "File not found";
		char tav = file.get();
		while (tav != EOF)
		{
			content.push_back(tav);
			tav = file.get();
		}
	}
	else content = "<!DOCTYPE HTML>\n<html><div><h3>Input is invalid</h3></div>\n<div><h4>Omer And Yarin Server</h4></div></html>";
	return content;
}


void stringQuery(string path, string* fileName, string* langParam)
{
	*fileName = path.substr(0, path.find('?'));
	string param = path.substr(path.find('?') + 1);
	string lang = param.substr(param.find('=') + 1);
	if (lang == *fileName)
	{
		*langParam = " ";
	}
	else
	{
		*langParam = lang;
	}

}

string deleteFile(string fileName)
{
	FILE* file = fopen(fileName.c_str(), "r");
	if (file != nullptr)
	{
		fclose(file);
		if (remove(fileName.c_str()) == 0)
		{
			return "HTTP/1.1 200 OK\r\n";
		}
		else
		{
			return "HTTP/1.1 500 Internal Server Error\r\n";
		}
	}
	else
	{
		return "HTTP/1.1 404 Not Found\r\n";
	}
}

string writeToFile(string fileName, string content)
{
	FILE* file = fopen(fileName.c_str(), "r");

	if (file != nullptr)
	{
		fclose(file);
		ofstream outputFile;
		outputFile.open(fileName);
		if (outputFile.is_open())
		{
			outputFile << content;
			outputFile.close();
			return "HTTP/1.1 201 Created\r\n";
		}
		else
		{
			return "HTTP/1.1 500 Internal Server Error\r\n";
		}
	}
	else
	{
		ofstream outputFile(fileName);
		outputFile << content;
		return "HTTP/1.1 201 Created\r\n";
	}
}

string createOpeningHeader(const string &body)
{
	string messageStatus = "HTTP/1.1 ";
	if (body.compare("File not found") == 0)
		messageStatus += "404 Not Found\r\n";
	else
		messageStatus += "200 OK\r\n";
	return messageStatus;
}

string headerToSend()
{
	time_t currentTime;
	string response;

	response.append("Date: ");
	time(&currentTime);
	response.append(ctime(&currentTime));
	response += "Server: Omer And Yarin Server\r\nContent-Type: text/html\r\nContent-length: ";
	return response;
}

string getSizeOfBodyMessage(const string& body)
{
	int len = body.length();
	string size = to_string(len);
	return size;
}

void parseHttpRequest(char* recvBuff, string& req)
{
	string tempBuff(recvBuff);

	if (tempBuff.find('\n') == string::npos)
	{
		tempBuff = "\0";
		req = tempBuff;
		return;
	}

	req = tempBuff.substr(0, tempBuff.find('\n'));
}


void findMethodOfHttpRequest(string &recvReq, int &subType)
{
	try
	{
		int res = -1;
		if (recvReq.compare("Exit") == 0)
			res = EXIT;

		string requestType = recvReq.substr(0, recvReq.find(' '));

		if (requestType.compare("GET") == 0)
			res = GET;

		else if (requestType.compare("PUT") == 0)
			res = PUT;

		else if (requestType.compare("DELETE") == 0)
			res = _DELETE;

		else if (requestType.compare("OPTIONS") == 0)
			res = OPTIONS;

		else if (requestType.compare("HEAD") == 0)
			res = HEAD;

		else if (requestType.compare("TRACE") == 0)
			res = TRACE;

		else if (requestType.compare("POST") == 0)
			res = POST;

		subType = res;
	}

	catch (const char* exp)
	{
		subType = ERROR_REQUEST;
	}
}



#endif
