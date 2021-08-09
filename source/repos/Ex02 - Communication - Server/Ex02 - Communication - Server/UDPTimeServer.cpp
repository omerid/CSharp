using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <ctime>

#define TIME_PORT	27015

clock_t startTime;
clock_t endTime;
bool timerOn = false;

bool initWinSocket(WSAData& wsaData);
bool connectionStart(WSAData& wsaData, SOCKET& connSocket, sockaddr_in& server);
bool socketStart(SOCKET& m_socket);
bool sendMsg(SOCKET& m_socket, char sendBuff[255], sockaddr& client_addr, int& client_addr_len);
bool reciveMsg(SOCKET& m_socket, char recvBuff[255], sockaddr& client_addr, int& client_addr_len);
bool bindSocket(SOCKET& m_socket, sockaddr_in& serverService);
void initAddressAndPort(sockaddr_in& serverService);
void handleRequests(SOCKET& connSocket);
void requestProcessing(char recvBuff[255], char sendBuff[255]);
void GetTimeWithoutDateInCity(char recvBuff[255], char sendBuff[255], int userRequestedCity);
void measureTimeLap(char recvBuff[255], char sendBuff[255]);
void timerCheck();
void GetSecondsSinceBeginingOfMonth(tm *timeinfo, char sendBuff[255]);
void GetDaylightSavings(tm *timeinfo, char sendBuff[255]);


void main()
{
	WSAData wsaData;
	SOCKET m_Socket;
	sockaddr_in server;

	if (!connectionStart(wsaData, m_Socket, server))
		return;

	handleRequests(m_Socket);

	cout << "Time Server: Some Error Occurred - Closing Connection.\n";
	closesocket(m_Socket);
	WSACleanup();

	system("pause");
}

void handleRequests(SOCKET& connSocket)
{
	sockaddr client_addr;
	int client_addr_len = sizeof(client_addr);
	char sendBuff[255];
	char recvBuff[255];

	while (1)
	{
		cout << "Time Server: Wait for clients' requests\n";
		if (reciveMsg(connSocket, recvBuff, client_addr, client_addr_len))
		{
			requestProcessing(recvBuff, sendBuff);
			if (!sendMsg(connSocket, sendBuff, client_addr, client_addr_len))
				return;
		}
	}
}

void requestProcessing(char recvBuff[255], char sendBuff[255])
{
	int userRequest;
	int userRequestedCity;
	time_t timer;
	tm *timeinfo;

	time(&timer);
	timeinfo = localtime(&timer);

	timerCheck();

	if (strlen(recvBuff) > 2)
	{

		userRequestedCity = recvBuff[2] - '0';
		recvBuff[1] = '\0';
		userRequest = 12;
	}
	else
		userRequest = atoi(recvBuff);


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
		GetSecondsSinceBeginingOfMonth(timeinfo, sendBuff);
		break;
	case 10:
		//GetWeekOfYear 
		strftime(sendBuff, 255, "%W", timeinfo);
		break;
	case 11:
		GetDaylightSavings(timeinfo, sendBuff);
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

void GetDaylightSavings(tm *timeinfo, char sendBuff[255])
{
	if (timeinfo->tm_isdst > 0)
		strcpy(sendBuff, "1");
	else if (timeinfo->tm_isdst == 0)
		strcpy(sendBuff, "0");
	else
		strcpy(sendBuff, "[No Information]");
}


void GetSecondsSinceBeginingOfMonth(tm *timeinfo, char sendBuff[255])
{
	int calculate;
	calculate = timeinfo->tm_mday * 24 * 60 * 60;
	calculate += timeinfo->tm_hour * 60 * 60;
	calculate += timeinfo->tm_min * 60;
	calculate += timeinfo->tm_sec;
	snprintf(sendBuff, 255, "%d", calculate);
}

void timerCheck()
{
	if (timerOn)
	{
		clock_t checkTimer = clock();
		clock_t clockTicksTaken = checkTimer - startTime;
		double timeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;
		if (timeInSeconds > 180) 
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
	case 1:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour+ 9)%24, ptm->tm_min, ptm->tm_sec);
		break;
	case 2:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour + 10) % 24, ptm->tm_min, ptm->tm_sec);
		break;
	case 3:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour + -7) % 24, ptm->tm_min, ptm->tm_sec);
		break;
	case 4:
		snprintf(sendBuff, 255, "%2d:%02d:%02d", (ptm->tm_hour + 1) % 24, ptm->tm_min, ptm->tm_sec);
		break;
	case 5:
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
		cout << "Time Server: Error at WSAStartup()\n";
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
		cout << "Time Server:: Error at recv(): " << WSAGetLastError() << endl;

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
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
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
		cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return false;
	}

	cout << "Time Server: Sent: " << bytesSent << "\\" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
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

	recvBuff[bytesRecv] = '\0'; 
	cout << "Time Server: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
	return true;
}