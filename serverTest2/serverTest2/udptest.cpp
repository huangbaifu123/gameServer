#include <Winsock2.h>
#include <cstdio>

#include <string.h>
#include <stdio.h>

#include<map>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define bufsize 1024 
#define UserNum 2		//�������

int main()
{

	//1 �����׽��� �󶨶˿�
	WSADATA wsaData;
	SOCKET sockServer;
	SOCKADDR_IN addrServer;
	SOCKADDR_IN tempClientAddr;

	map<SOCKADDR_IN, bool> strMap;

	SOCKADDR_IN ClientAddrList[UserNum] ;

	int str_len ;
	char message[bufsize] = "\0";
	int     nRet;
	int     len = sizeof(SOCKADDR);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sockServer = socket(AF_INET, SOCK_DGRAM, 0);
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//INADDR_ANY��ʾ�κ�IP
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//�󶨶˿�6000
	nRet = bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("bind failed !/n");
		closesocket(sockServer);
		WSACleanup();
		return -1;
	}


	int key = 0;

	//2 ����ѭ�����������Ϣ �뷢����Ϣ
	printf("������������udp:\n������...\n");
	while (true)
	{
			str_len = recvfrom(sockServer, message, bufsize, 0, (SOCKADDR*)&tempClientAddr, &len);
			if (SOCKET_ERROR != str_len )
			{
				if (key == UserNum)
				{

				}
				else {
					//std::map<SOCKADDR_IN, bool>::iterator it = strMap.end();
					//strMap.insert(it, pair<SOCKADDR_IN, bool>(tempClientAddr, true));
					printf("recv �������id�� %d \n", key);
					ClientAddrList[key] = tempClientAddr;
					key++;
				}
			}

		for (int i = 0; i < UserNum; i++)
		{
				//printf("send %d  %d\n", i, ClientAddrList[i]);
			str_len = sendto(sockServer, message, bufsize, 0, (SOCKADDR*)&ClientAddrList[i], len);
			if (SOCKET_ERROR != str_len)
			{
				printf("send ���������id�� %d\n", i);
			}
		}
	}

	WSACleanup();
}