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
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//INADDR_ANY��ʾ�κ�IP
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//�󶨶˿�6000
	bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	//Listen������
	listen(sockServer, 5);//5Ϊ�ȴ�������Ŀ
	printf("������������:\n������...\n");
	int len = sizeof(SOCKADDR);
	char ch[5] = "";
	while (true)
	{
		Sleep(0);
		SOCKET sockClient;
		SOCKADDR_IN addrClient;
		//���������̣�ֱ���пͻ�����������Ϊֹ
		sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);
		//���ղ���ӡ�ͻ�������
		char recvBuf[255] = { 0 };
		recv(sockClient, recvBuf, 100, 0);
		printf("[������Ϣ]%s\n", recvBuf);

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

		//�ر�socket
		closesocket(sockClient);
	}

	WSACleanup();
}