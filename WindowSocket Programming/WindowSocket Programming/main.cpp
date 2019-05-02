
//Win Client

#include <iostream>
#include <stdlib.h>
#include <WinSock2.h>
void ErrorHandling(const char* message);
using namespace std;

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;// 소켓 주소

	char message[30];
	int strLen = 0;
	int idx = 0, readLen = 0;

	if (argc != 3)
	{
		cout << "Usage:" << argv[0] << "<IP> <port>" << endl;
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // MAKEWORD(2,2)가 뭐였더라?
	{
		ErrorHandling("WSAStartup() error!");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0); //Socket 생성 ,SOCK_STREAM 이뭐엿지?


	if (hSocket == INVALID_SOCKET)
		ErrorHandling("hSocket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2])); // atoi가뭐였더라 , argv는 어떻게나뉘는거엿지?

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) // connect 함수를통한 서버와 연결
	{
		ErrorHandling("connect() error!");
	}

	while (readLen = recv(hSocket, &message[idx++], 1, 0))// recv함수에서  길이를 나중에늘려보자
	{

		if (readLen == -1)
		{
			ErrorHandling("read() error!");
		}
		strLen += readLen;
	}

	cout << "Message from server :" << message << endl;
	cout << "Function Read Call Count" << strLen << endl;

	closesocket(hSocket);
	WSACleanup();
	return 0;

}
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

