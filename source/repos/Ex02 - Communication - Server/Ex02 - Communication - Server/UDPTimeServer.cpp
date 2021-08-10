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
bool    timerOn = false;

bool initWinSocket(WSAData& wsaData);
bool openConnection(WSAData& wsaData, SOCKET& m_socket, sockaddr_in& server);
bool socketStart(SOCKET& m_socket);
bool messageSender(SOCKET& m_socket, char sendBuff[255], sockaddr& client_addr, int& client_addr_len);
bool receiveMessage(SOCKET& m_socket, char receiveBuff[255], sockaddr& client_addr, int& client_addr_len);
bool sockerBinder(SOCKET& m_socket, sockaddr_in& serverService);
void initAddressAndPort(sockaddr_in& serverService);
void handleRequests(SOCKET& connectionSocket);
void processRequests(char receiveBuff[255], char sendBuff[255]);
void GetTimeWithoutDateInCity(char receiveBuff[255], char sendBuff[255], int requestedCity);
void timeLapMeasurer(char receiveBuff[255], char sendBuff[255]);
void timeValidator();
void GetBegginingOfMonthSeconds(tm *timeinfo, char sendBuff[255]);
void GetDaylightSavings(tm *timeinfo, char sendBuff[255]);
bool handleClientRequest(SOCKET& connectionSocket, char sendBuff[255], char receiveBuff[255], sockaddr &client_addr, int client_addr_len);


void main()
{
	wsaData     wsaData;
	SOCKET      m_Socket;
	sockaddr_in server;

	if (!openConnection(wsaData, m_Socket, server))
		return;

	handleRequests(m_Socket);

	cout << "Time Server: An internal error has occurred, - Closing connection pool.\n";
	closesocket(m_Socket);
	WSACleanup();

	system("pause");
}

void handleRequests(SOCKET& connectionSocket)
{
	sockaddr client_addr;
	int  client_addr_len = sizeof(client_addr);
	char sendBuff[255];
	char receiveBuff[255];

	while (1)
	{
		cout << "Server: Wait for clients' requests\n";
		handleClientRequest(connectionSocket, sendBuff, receiveBuff, client_addr, client_addr_len);
	}
}

bool handleClientRequest(SOCKET& connectionSocket, char sendBuff[255], char receiveBuff[255], sockaddr &client_addr, int client_addr_len)
{
	if (receiveMessage(connectionSocket, receiveBuff, client_addr, client_addr_len))
	{
		processRequests(receiveBuff, sendBuff);
		if (!messageSender(connectionSocket, sendBuff, client_addr, client_addr_len))
			return false;
		return true;
	}
	return false;
}

void processRequests(char receiveBuff[255], char sendBuff[255])
{
	int    userRequest;
	int    requestedCity;
	time_t timer;
	tm *timeinfo;

	time(&timer);
	timeinfo = localtime(&timer);

	timeValidator();

	if (strlen(receiveBuff) > 2)
	{

		requestedCity = receiveBuff[2] - '0';
		receiveBuff[1] = '\0';
		userRequest = 12;
	}
	else
		userRequest = atoi(receiveBuff);


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
		GetBegginingOfMonthSeconds(timeinfo, sendBuff);
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
		GetTimeWithoutDateInCity(receiveBuff, sendBuff, requestedCity);
		break;
	case 13:
		//timeLapMeasurer 
		timeLapMeasurer(receiveBuff, sendBuff);
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


void GetBegginingOfMonthSeconds(tm *timeinfo, char sendBuff[255])
{
	int seconds;
	seconds =  timeinfo->tm_mday * 24 * 60 * 60;
	seconds += timeinfo->tm_hour * 60 * 60;
	seconds += timeinfo->tm_min * 60;
	seconds += timeinfo->tm_sec;
	snprintf(sendBuff, 255, "%d", seconds);
}

void timeValidator()
{
	if (timerOn)
	{
		clock_t clockTimer 		= clock();
		clock_t clockTicksTaken = clockTimer - startTime;
		double  timeInSeconds 	= clockTicksTaken / (double)CLOCKS_PER_SEC;
		if (timeInSeconds > 180) 
			timerOn = false;
	}
}

void timeLapMeasurer(char receiveBuff[255], char sendBuff[255])
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

void GetTimeWithoutDateInCity(char receiveBuff[255], char sendBuff[255], int requestedCity)
{
	time_t rawTime;
	struct tm * ptm;

	time(&rawTime);
	ptm = gmtime(&rawTime);

	switch (requestedCity)
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
	bool retVal = true;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Server: Error at WSAStartup()\n";
		retVal = false;
	}
	return retVal;
}

bool openConnection(WSAData& wsaData, SOCKET& m_socket, sockaddr_in& server)
{
	bool error = false;

	if (initWinSocket(wsaData) && socketStart(m_socket))
		initAddressAndPort(server);
	else
		error = true;

	if (!sockerBinder(m_socket, server))
		error = true;

	return !error;
}

bool socketStart(SOCKET& m_socket)
{
	bool retVal = true;
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket)
	{
		cout << "Time Server:: Error at recv(): " << WSAGetLastError() << endl;

		WSACleanup();
		retVal = false;
	}

	return retVal;
}

void initAddressAndPort(sockaddr_in& serverService)
{
	serverService.sin_family 	  = AF_INET;
	serverService.sin_addr.s_addr = INADDR_ANY;	
	serverService.sin_port 		  = htons(TIME_PORT);
}

bool sockerBinder(SOCKET& m_socket, sockaddr_in& serverService) 
{
	bool retVal = true;
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR *)&serverService, sizeof(serverService)))
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		retVal = false;
	}
	return retVal;
}

bool messageSender(SOCKET& m_socket, char sendBuff[255], sockaddr& client_addr, int& client_addr_len)
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

bool receiveMessage(SOCKET& m_socket, char receiveBuff[255], sockaddr& client_addr, int& client_addr_len)
{
	bool retVal = true;
	int bytesRecv = bytesRecv = recvfrom(m_socket, receiveBuff, 255, 0, &client_addr, &client_addr_len);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Server: Error at recvfrom(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		retVal = false;
	}

	receiveBuff[bytesRecv] = '\0'; 
	cout << "Time Server: Recieved: " << bytesRecv << " bytes of \"" << receiveBuff << "\" message.\n";
	return retVal;
}
