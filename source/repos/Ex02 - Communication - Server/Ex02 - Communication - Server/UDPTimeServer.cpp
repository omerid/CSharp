#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <ctime>

#define TOKYO	1
#define MELBOURNE	2
#define SAN_FRANCISCO	3
#define PORTO	4
#define OTHER	5
#define JST 9
#define AEST 10
#define PDT -7
#define WEST 1
#define THREE_MINUTES 180 // 180 Seconds == 3 Minutes

#define TIME_PORT	27015

clock_t startTime;
clock_t endTime;
bool timerOn = false;

bool initWinSocket(WSAData& wsaData);
bool connectionStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server);
bool socketStart(SOCKET& m_socket);
void initAddressAndPort(sockaddr_in& serverService);
bool bindSocket(SOCKET& m_socket, sockaddr_in& serverService);
void handleClientRequest(SOCKET& connSocket);
bool sendMsg(SOCKET& m_socket, char sendBuff[255], sockaddr& client_addr, int& client_addr_len);
bool reciveMsg(SOCKET& m_socket, char recvBuff[255], sockaddr& client_addr, int& client_addr_len);
bool handleClientRequestHelper(SOCKET& connSocket, char sendBuff[255], char recvBuff[255], sockaddr &client_addr, int client_addr_len);
void requestProcessing(char recvBuff[255], char sendBuff[255]);
void GetTimeWithoutDateInCity(char recvBuff[255], char sendBuff[255], int userRequestedCity);
void measureTimeLap(char recvBuff[255], char sendBuff[255]);
void checkTheTimer();

void main()
{
	WSAData wsaData; 
	SOCKET m_socket;
	sockaddr_in serverService;

	if (connectionStart(wsaData, m_socket, serverService))
		if (bindSocket(m_socket, serverService))
			handleClientRequest(m_socket);
		
	// Closing connections and Winsock.
	cout << "[Server] Some Error Occurred - Closing Connection.\n";
	closesocket(m_socket);
	WSACleanup();
}

void handleClientRequest(SOCKET& connSocket)
{
	sockaddr client_addr;
	int client_addr_len = sizeof(client_addr);
	char sendBuff[255];
	char recvBuff[255];

	while (true)
	{
		cout << "[Server] Wait for clients' requests\n";
		handleClientRequestHelper(connSocket, sendBuff, recvBuff, client_addr, client_addr_len);
	}
}

bool handleClientRequestHelper(SOCKET& connSocket, char sendBuff[255], char recvBuff[255], sockaddr &client_addr, int client_addr_len)
{
	if (reciveMsg(connSocket, recvBuff, client_addr, client_addr_len))
	{
		requestProcessing(recvBuff, sendBuff);
		if (!sendMsg(connSocket, sendBuff, client_addr, client_addr_len))
			return false;
		return true;
	}
	return false;
}

void requestProcessing(char recvBuff[255], char sendBuff[255])
{
	int userRequest;
	int userRequestedCity;

	checkTheTimer();

	if (strlen(recvBuff) > 2)
	{
		if (recvBuff[1] == ',')
		{
			userRequestedCity = recvBuff[2] - '0';
			recvBuff[1] = '\0';
		}
		if (recvBuff[2] == ',')
		{
			userRequestedCity = recvBuff[3] - '0';
			recvBuff[2] = '\0';
		}
	}

	userRequest = atoi(recvBuff);
	time_t timer;
	time(&timer);
	tm *timeinfo;
	timeinfo = localtime(&timer);
	int calculate;

	switch (userRequest)
	{
	case 1:
		//GetTime
		strcpy(sendBuff, ctime(&timer));
		sendBuff[strlen(sendBuff) - 1] = '\0';
		break;
	case 2:
		//GetTimeWithoutDate 
		strftime(sendBuff, 255, "%X", timeinfo);
		break;
	case 3:
		//GetTimeSinceEpoch 
		snprintf(sendBuff, 255, "%lld", timer);
		break;
	case 4:
		//GetClientToServerDelayEstimation
		snprintf(sendBuff, 255, "%ld", GetTickCount());
		break;
	case 5:
		//MeasureRTT  
		snprintf(sendBuff, 255, "%ld", GetTickCount());
		break;
	case 6:
		//GetTimeWithoutDateOrSeconds 
		strftime(sendBuff, 255, "%R", timeinfo);
		break;
	case 7:
		//GetYear 
		strftime(sendBuff, 255, "%Y", timeinfo);
		break;
	case 8:
		//GetMonthAndDay  
		strftime(sendBuff, 255, "%d/%m", timeinfo);
		break;
	case 9:
		//GetSecondsSinceBeginingOfMonth 
		calculate = timeinfo->tm_mday * 24 * 60 * 60;
		calculate += timeinfo->tm_hour * 60 * 60;
		calculate += timeinfo->tm_min * 60;
		calculate += timeinfo->tm_sec;
		snprintf(sendBuff, 255, "%d", calculate);
		break;
	case 10:
		//GetWeekOfYear 
		strftime(sendBuff, 255, "%W", timeinfo);
		break;
	case 11:
		//GetDaylightSavings 
		if(timeinfo->tm_isdst > 0)
			strcpy(sendBuff, "1");
		else if(timeinfo->tm_isdst == 0)
			strcpy(sendBuff, "1");
		else
			strcpy(sendBuff, "[No Information]");
		break;
	case 12:
		//GetTimeWithoutDateInCity 
		GetTimeWithoutDateInCity(recvBuff, sendBuff, userRequestedCity);
		break;
	case 13:
		//MeasureTimeLap 
		measureTimeLap(recvBuff, sendBuff);
		break;
	default:
		break;
	}
}

void checkTheTimer()
{
	if (timerOn)
	{
		clock_t checkTimer = clock();
		clock_t clockTicksTaken = checkTimer - startTime;
		double timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		if (timeInSeconds > THREE_MINUTES)
			timerOn = false;
	}
}

void measureTimeLap(char recvBuff[255], char sendBuff[255])
{
	if (timerOn)
	{
		endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		double timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		snprintf(sendBuff, 255, "%lf seconds", timeInSeconds);
		timerOn = false;
	}
	else
	{
		strcpy(sendBuff, "Start measure lap time");
		startTime = clock();
		timerOn = true;
	}
}

void GetTimeWithoutDateInCity(char recvBuff[255], char sendBuff[255], int userRequestedCity)
{
	time_t rawtime;
	struct tm * ptm;

	time(&rawtime);
	ptm = gmtime(&rawtime);

	switch (userRequestedCity)
	{
	case TOKYO:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour+ JST)%24, ptm->tm_min, ptm->tm_sec);
		break;
	case MELBOURNE:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour + AEST) % 24, ptm->tm_min, ptm->tm_sec);
		break;
	case SAN_FRANCISCO:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour + PDT) % 24, ptm->tm_min, ptm->tm_sec);
		break;
	case PORTO:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour + WEST) % 24, ptm->tm_min, ptm->tm_sec);
		break;
	case OTHER:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
		break;
	default:
		break;
	}
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

bool connectionStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server)
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
		cout << "[Server]: Error at recv(): " << WSAGetLastError() << endl;

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

	int bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "[Server] Error at sendto(): " << WSAGetLastError() << endl;
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
		cout << "[Server] Error at recvfrom(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return false;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	cout << "[Server] Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
	return true;
}