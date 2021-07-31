#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define TIME_PORT	27015

bool initWinSocket(WSAData& wsaData);
bool connectiontStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server);
bool socketStart(SOCKET& m_socket);
void initAddressAndPort(sockaddr_in& serverService);
bool bindSocket(SOCKET& m_socket, sockaddr_in& serverService);
void handleClientRequest(SOCKET& connSocket);
bool sendMsg(SOCKET& m_socket, char sendBuff[255], sockaddr& client_addr, int& client_addr_len);
bool reciveMsg(SOCKET& m_socket, char recvBuff[255], sockaddr& client_addr, int& client_addr_len);

void main()
{
	WSAData wsaData; 
	SOCKET m_socket;
	sockaddr_in serverService;

	if (connectiontStart(wsaData, m_socket, serverService))
		if (bindSocket(m_socket, serverService))
			handleClientRequest(m_socket);
		else
			return;
	else
		return;
	
	// Closing connections and Winsock.
	cout << "Time Server: Closing Connection.\n";
	closesocket(m_socket);
	WSACleanup();
}

void handleClientRequest(SOCKET& connSocket)
{
	sockaddr client_addr;
	int client_addr_len = sizeof(client_addr);
	int bytesSent = 0;
	char sendBuff[255];
	char recvBuff[255];



	cout << "[Server] Wait for clients' requests.\n";

}


bool initWinSocket(WSAData& wsaData)
{
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "[Server] Error at WSAStartup()\n";
		return false;
	}
	return true;
}

bool connectStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server)
{
	if (initWinSocket(wsaData) && socketStart(connSocket))
	{
		initAddressAndPort(server);
		return true;
	}
	else
		return false;
}


bool socketStart(SOCKET& m_socket)
{
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;

		WSACleanup();
		return false;
	}
	else
		return true;
}

void initAddressAndPort(sockaddr_in& serverService)
{
	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = INADDR_ANY;	//inet_addr("127.0.0.1");
	serverService.sin_port = htons(TIME_PORT);
}

bool bindSocket(SOCKET& m_socket, sockaddr_in& serverService) 
{
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR *)&serverService, sizeof(serverService)))
	{
		cout << "[Server] Error at bind(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return false;
	}
	return true;
}

bool sendMsg(SOCKET& m_socket, char sendBuff[255], sockaddr& client_addr, int& client_addr_len)
{

	time_t timer;
	time(&timer);
	// Parse the current time to printable string.
	strcpy(sendBuff, ctime(&timer));
	sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string

	// Sends the answer to the client, using the client address gathered
	// by recvfrom. 
	int bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return false;
	}

	cout << "[Server] Sent: " << bytesSent << "\\" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	return true;
}

bool reciveMsg(SOCKET& m_socket, char recvBuff[255], sockaddr& client_addr, int& client_addr_len)
{
	int bytesRecv = bytesRecv = recvfrom(m_socket, recvBuff, 255, 0, &client_addr, &client_addr_len);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Server: Error at recvfrom(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return false;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	cout << "[Server] Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
	return true;
}
