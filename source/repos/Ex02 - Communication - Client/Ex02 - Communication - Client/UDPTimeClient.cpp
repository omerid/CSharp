#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>


#define TIME_PORT	27015

bool  initWinSocket(WSAData& wsaData);
bool  connectiontStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server);
bool  socketStart(SOCKET& connSocket);
void  initAddressAndPort(sockaddr_in& server);
bool  sendMsg(SOCKET& connSocket, char sendBuff[255], sockaddr_in& server);
bool  reciveMsg(SOCKET& connSocket, char reciveBuff[255]);
void  handleUserRequest(SOCKET& connSocket, sockaddr_in& server);
bool  GetClientToServerDelayEstimation(SOCKET& connSocket, char sendBuff[255], char reciveBuff[255], sockaddr_in& server);
int   getChoiceFromUser();
void  showMenu();
int   getCityNumberFromUser();
float getAvgTS(DWORD reciveLong[], int reciveLen);
bool  measureRTT(char sendBuff[255], char recvBuff[255], SOCKET& connSocket, sockaddr_in& server);

void main()
{
	WSAData wsaData;
	SOCKET connSocket;
	sockaddr_in server;

	if (connectiontStart(wsaData, connSocket, server))
		handleUserRequest(connSocket, server);
	else return;
	
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}

void handleUserRequest(SOCKET& connSocket, sockaddr_in& server)
{
	char sendBuff[255];
	char recvBuff[255];
	int userChoice;

	while (true)
	{
		if ((userChoice = getChoiceFromUser()) == 0)
		{
			cout << "Client: Quit Request Was Processed" << endl;
			break;
		}
		else
		{
			if (userChoice == 12)
			{
				int cityNumberFromUser = getCityNumberFromUser();
				snprintf(sendBuff, 255, "%d,%d", userChoice, cityNumberFromUser);
			}
			else
				snprintf(sendBuff, 255, "%d", userChoice);

			if (userChoice == 4)
			{
				if (!GetClientToServerDelayEstimation(connSocket, sendBuff, recvBuff, server))
					break;
			}
			else if (userChoice == 5)
			{
				if (!measureRTT(sendBuff, recvBuff, connSocket, server))
					break;
			}
			else
			{
				if (!sendMsg(connSocket, sendBuff, server) || !reciveMsg(connSocket, recvBuff))
					break;
			}
		}
	}
}


int getCityNumberFromUser()
{
	int userInput;
	char dummyCity[255];

	cout << "Please select one of the cities" << endl;
	cout << "1.  Tokyo, Japan" << endl;
	cout << "2.  Melbourne, Australia" << endl;
	cout << "3.  San Francisco, USA" << endl;
	cout << "4.  Porto, Portugal" << endl;
	cout << "5.  Other. Please Enter The Requested City:" << endl;

	while (true)
	{
		cin >> userInput;
		if (userInput >= 1 && userInput <= 5)
		{
			if (userInput == 5)
				cin >> dummyCity;
			break;
		}
		else
			cout << "Client: Invalid Parameter Value. Please Enter Value in 1-5 Range" << endl;
	}
	return userInput;

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

bool connectiontStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server)
{
	if (initWinSocket(wsaData) && socketStart(connSocket))
	{
		initAddressAndPort(server);
		return true;
	}
	else
		return false;
}

bool socketStart(SOCKET& connSocket)
{
	connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "[Client] Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	else
		return true;
}

void initAddressAndPort(sockaddr_in& server)
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);
}

bool sendMsg(SOCKET& connSocket, char sendBuff[255], sockaddr_in& server)
{
	int bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "[Client] Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return false;
	}
	cout << "[Client] Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	return true;
}

bool reciveMsg(SOCKET& connSocket, char reciveBuff[255])
{
	int bytesRecv = recv(connSocket, reciveBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "[Client] Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return false;
	}
	reciveBuff[bytesRecv] = '\0'; 
	cout << "[Time Client] Recieved: " << bytesRecv << " bytes of \"" << reciveBuff << "\" message." << endl;
	return true;
}

bool GetClientToServerDelayEstimation(SOCKET& connSocket, char sendBuff[255], char reciveBuff[255], sockaddr_in& server)
{
	DWORD reciveLong[100];

	for (size_t i = 0; i < 100; i++)
	{
		if (!sendMsg(connSocket, sendBuff, server))
			return false;
	}
	for (size_t i = 0; i < 100; i++)
	{
		if (!reciveMsg(connSocket, reciveBuff))
			return false;
		reciveLong[i] = atol(reciveBuff); // GetTickCount return DWORD value, which is LONG (4 bytes, 32 bits)
	}

	float averageTimeStamp = getAvgTS(reciveLong, 100);

	cout << "[Client] The Delay is: " << averageTimeStamp << "ms" << endl;
	return true;
}


bool measureRTT(char sendBuff[255], char recvBuff[255], SOCKET& connSocket, sockaddr_in& server)
{
	DWORD sum = 0;
	DWORD recvClickCounter;
	DWORD sendClickCounter;

	for (int i = 0; i < 100; i++)
	{
		sendClickCounter = GetTickCount();
		if(sendMsg(connSocket, sendBuff, server))
		{
			if (!reciveMsg(connSocket, recvBuff))
				return false;
		}
		else
			return false;

		recvClickCounter = GetTickCount();
		sum += (recvClickCounter - sendClickCounter);
	}

		cout << "Time Client: Measure RTT: " << (sum) / 100 << " milliseconds" << endl;
	return true;
}

float getAvgTS(DWORD reciveLong[], int reciveLen)
{
	float avg = 0;
	for (size_t i = 1; i < reciveLen; i++)
	{
		avg = avg + reciveLong[i] - reciveLong[i - 1];
	}
	avg - avg - reciveLen;
	return avg;
}

int getChoiceFromUser() 
{
	showMenu();
	int inputFromUser;

	while (true)
	{
		cin >> inputFromUser;
		if (inputFromUser >= 0 && inputFromUser <= 13)
			break;
		else
			cout << "[Client] Invalid Parameter Value. Please Enter Value in 0-13 Range" << endl;
	}
	return inputFromUser;
}

void showMenu() 
{
	cout << "==========================================" << endl;
	cout << "||             Client Menu              ||" << endl;
	cout << "==========================================" << endl;
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
	cout << "---> Please Enter Your Choice <---" << endl;
}
