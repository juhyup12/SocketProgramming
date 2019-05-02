

#include <iostream>
#include <WinSock2.h>
using namespace std;

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	cout << argv[0] << endl;
	cout << argc << endl;

	WSADATA wsaData;
	SOCKET hServSock, hCIntSock; // Socket을 2개만드네?
	SOCKADDR_IN servAddr, cIntAddr; // Server 주소와 Client 주소정보 2개를 만드네?


	int szCIntAddr;
	char message[] = "Hello World"; // 메시지네?
	if (argc != 2)
	{
		cout << "Usage : %s <port>" << argv[0] << endl;
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;// IPV4
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY에 대해서
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() Error");

	szCIntAddr = sizeof(cIntAddr);
	hCIntSock = accept(hServSock, (SOCKADDR*)&cIntAddr, &szCIntAddr);// listen과 Accept의 차이..?  
	//accept하면 Client의 소켓을 받아오나보다

	if (hCIntSock == INVALID_SOCKET)
	{
		ErrorHandling("Accept() error!");
	}

	send(hCIntSock, message, sizeof(message), 0);
	closesocket(hCIntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
   
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}

