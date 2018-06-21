#include <Winsock2.h>
#include <cstdio>

#include <string.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

void main1()
{
	WSADATA wsaData;
	SOCKET sockServer;
	SOCKADDR_IN addrServer;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//INADDR_ANY表示任何IP
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//绑定端口6000
	bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	//Listen监听端
	listen(sockServer, 5);//5为等待连接数目
	printf("服务器已启动:\n监听中...\n");
	int len = sizeof(SOCKADDR);
	char ch[5] = "";
	while (true)
	{
		Sleep(0);
		SOCKET sockClient;
		SOCKADDR_IN addrClient;
		//会阻塞进程，直到有客户端连接上来为止
		sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);
		//接收并打印客户端数据
		char recvBuf[255] = { 0 };
		recv(sockClient, recvBuf, 100, 0);
		printf("[接受信息]%s\n", recvBuf);

		send(sockClient, recvBuf, strlen(recvBuf), 0);

		if (strcmp(recvBuf, "1") == 0)
		{
			const char * split = ",";
			char * p;
			p = strtok(recvBuf, split);
			while (p != NULL) {
				printf("%s\n", p);
				p = strtok(NULL, split);
			}
			const char * sendData = "hello,TCP Client\n";
			send(sockClient, sendData, strlen(sendData), 0);
		}
		else if (strcmp(recvBuf, "2") == 0)
		{

		}

		//关闭socket
		closesocket(sockClient);
	}

	WSACleanup();
}