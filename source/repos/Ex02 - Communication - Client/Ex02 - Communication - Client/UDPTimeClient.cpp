#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <string.h>
#include <winsock2.h> 
using namespace std;


#define TIME_PORT	27015

bool  initWinSocket(WSAData& wsaData);
bool  connectiontStart(WSAData& wsaData, SOCKET& m_socket, sockaddr_in& server);
bool  publishMessage(SOCKET& connSocket, char sendBuff[255], sockaddr_in& server);
void  initAddPort(sockaddr_in& server);
bool  openSocket(SOCKET& connSocket);
bool  receiveMessage(SOCKET& connSocket, char reciveBuff[255]);
bool  GetClientToServerDelayEstimation(SOCKET& connSocket, char sendBuff[255], char reciveBuff[255], sockaddr_in& server);
bool  measureRTT(char sendBuff[255], char recvBuff[255], SOCKET& connSocket, sockaddr_in& server);
void  handleRequests(SOCKET& connSocket, sockaddr_in& server);
void  menu();
void  showCities();
void  closeConnection(SOCKET &m_Socket);
bool  inputValidator(int validNumber);
int   getUserChoice();
int   getCityNumberFromUser();


void main()
{
	wsaData 	wsaData;
	SOCKET 		m_Socket;
	sockaddr_in server;

	initWinSocket(wsaData);

	if (!connectiontStart(wsaData, m_Socket, server))
		return;

	handleRequests(m_Socket, server);

	closeConnection(m_Socket);

	system("pause");

}

void closeConnection(SOCKET &m_Socket)
{
	cout << "Time Client: Closing Connection.\n";
	closesocket(m_Socket);
}

void handleRequests(SOCKET& connSocket, sockaddr_in& server)
{
	char sendBuff[255];
	char recvBuff[255];
	int  userChoice;

	while (1)
	{
		userChoice = getUserChoice();

		if (userChoice == 0)
			cout << "Time Client: Quit request" << endl;
		
		else
		{
			if (userChoice == 12)
			{
				int cityNumberFromUser = getCityNumberFromUser();
				snprintf(sendBuff, 255, "%d,%d", cityNumberFromUser, userChoice);
			}
			else
				snprintf(sendBuff, 255, "%d", userChoice);

			if (userChoice == 4)
			{
				if (GetClientToServerDelayEstimation(connSocket, sendBuff, recvBuff, server) == false)
					break;
			}
			else if (userChoice == 5)
			{
				if (measureRTT(sendBuff, recvBuff, connSocket, server) == false)
					break;
			}
			else
			{
				if (publishMessage(connSocket, sendBuff, server) == false || receiveMessage(connSocket, recvBuff) == false)
					break;
			}
		}

		cout  << endl;

	}
}

int getCityNumberFromUser()
{
	int  input;
	char city[255];

	showCities();

	while (1)
	{
		cin >> input;
		if (inputValidator(input))
		{
			if (input == 5)
			{
				cout << "Please Enter The Requested City:" << endl;
				cin >> city;
			}
			break;
		}
		else
			cout << "Time Client: Invalid. Please enter this values: 1-5" << endl;
	}
	return input;
}

void showCities()
{
	cout << "Please select one city" << endl;
	cout << "1.  Tokyo, Japan" << endl;
	cout << "2.  Melbourne, Australia" << endl;
	cout << "3.  San Francisco, USA" << endl;
	cout << "4.  Porto, Portugal" << endl;
	cout << "5.  Other" << endl;
}

bool inputValidator(int validNumber)
{
	return validNumber >= 1 && validNumber <= 5;
}

bool initWinSocket(WSAData& wsaData)
{
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return false;
	}
	else
		return true;
}

bool connectiontStart(WSAData& wsaData, SOCKET& m_socket, sockaddr_in& server)
{
	initWinSocket(wsaData);
	if (!openSocket(m_socket))
		return false;
	initAddPort(server);
	return true;
}

bool openSocket(SOCKET& connSocket)
{
	connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	
	return true;
}

void initAddPort(sockaddr_in& server)
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);
}

bool publishMessage(SOCKET& connSocket, char sendBuff[255], sockaddr_in& server)
{
	int bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return false;
	}
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	return true;
}

bool receiveMessage(SOCKET& connSocket, char reciveBuff[255])
{
	int bytesRecv = recv(connSocket, reciveBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return false;
	}
	reciveBuff[bytesRecv] = '\0'; 
	cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << reciveBuff << "\" message." << endl;
	return true;
}

bool GetClientToServerDelayEstimation(SOCKET& connSocket, char sendBuff[255], char reciveBuff[255], sockaddr_in& server)
{
	DWORD receiveLong[100];
	bool error = false;

	for (int i = 0; i < 100; i++)
		if (publishMessage(connSocket, sendBuff, server) == false)
			error = true;

	for (int i = 0; i < 100; i++)
	{
		if (receiveMessage(connSocket, reciveBuff) == false)
			error = true;
		receiveLong[i] = atol(reciveBuff); 
	}

	float avg = 0;
	for (int i = 1; i < 100; i++)
		avg = avg + receiveLong[i] - receiveLong[i - 1];

	cout << "Time Client: The Delay is: " << avg/100 << "Milliseconds" << endl;
	return !error;
}

bool measureRTT(char sendBuff[255], char recvBuff[255], SOCKET& connSocket, sockaddr_in& server)
{
	DWORD sum = 0;
	DWORD recvClickCounter;
	DWORD sendClickCounter;
	bool  error = false;

	for (int i = 0; i < 100; i++)
	{
		sendClickCounter = GetTickCount();
		if(publishMessage(connSocket, sendBuff, server))
			if (receiveMessage(connSocket, recvBuff) == false)
				error = true;

		recvClickCounter = GetTickCount();
		sum += (recvClickCounter - sendClickCounter);
	}

		cout << "Time Client: Measure RTT: " << (sum) / 100 << " milliseconds" << endl;
	return !error;
}

int getUserChoice() 
{
	menu();
	int input;

	while (true)
	{
		cin >> input;
		if (input >= 0 && input <= 13)
			break;
		else
			cout << "Time Client: Invalid input. Please enter value in 0-13 range" << endl;
	}
	return input;
}

void menu() 
{
	cout << "    Client Menu:" << endl;
	cout << "1.  Get Time" << endl;
	cout << "2.  Get Time Without Date" << endl;
	cout << "3.  Get Time Since Epoch" << endl;
	cout << "4.  Get Client To Server Delay Estimation" << endl;
	cout << "5.  Get Measure RTT" << endl;
	cout << "6.  Get Time Without Date Or Seconds" << endl;
	cout << "7.  Get Year" << endl;
	cout << "8.  Get Month And Day" << endl;
	cout << "9.  Get Seconds Since Begining Of Month" << endl;
	cout << "10. Get Week Of Year" << endl;
	cout << "11. Get Daylight Savings" << endl;
	cout << "12. Get Time Without Date In City" << endl;
	cout << "13. Measure Time Lap" << endl;
	cout << "0.  Quit" << endl;
	cout << "Enter Your Choice: " << endl;
}
