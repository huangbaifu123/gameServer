#include <Winsock2.h>
#include <cstdio>

#include <string.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

#define bufsize 1024 

int main()
{
	WSADATA wsaData;
	SOCKET sockServer;
	SOCKADDR_IN addrServer;
	SOCKADDR_IN clientAddr;
	SOCKADDR_IN clientAddr2;
	SOCKADDR_IN tempClientAddr;

	int str_len ;
	char message[bufsize] = "\0";

	int     nRet;
	int     len = sizeof(SOCKADDR);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sockServer = socket(AF_INET, SOCK_DGRAM, 0);
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//INADDR_ANY表示任何IP1111
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//绑定端口6000
	nRet = bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("bind failed !/n");
		closesocket(sockServer);
		WSACleanup();
		return -1;
	}

	bool is_player = false;
	bool is_player2 = false;

	//Listen监听端
	printf("服务器已启动udp:\n监听中...\n");
	while (true)
	{
		if (!is_player)
		{
			str_len = recvfrom(sockServer, message, bufsize, 0, (SOCKADDR*)&clientAddr, &len);
			if (SOCKET_ERROR != nRet)
				is_player = true;
		}
		else if (!is_player2)
		{
			str_len = recvfrom(sockServer, message, bufsize, 0, (SOCKADDR*)&clientAddr2, &len);
			if (SOCKET_ERROR != nRet || &clientAddr2 != &clientAddr)
				is_player2 = true;
		}
		else
		{
			str_len = recvfrom(sockServer, message, bufsize, 0, (SOCKADDR*)&tempClientAddr, &len);
		}

		//printf("udp:receivefrom:\n ", message);
		sendto(sockServer, message, bufsize, 0, (SOCKADDR*)&clientAddr, len);
		sendto(sockServer, message, bufsize, 0, (SOCKADDR*)&clientAddr2, len);
	}

	WSACleanup();
}