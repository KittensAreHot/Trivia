#pragma once
#include <WinSock2.h>

class ConnectionHandler
{
private:
	static const int DATA_MAX_LEN = 1024;
public:
	static int Send(SOCKET clientSocket, char* data, int length);
	static int Recv(SOCKET clientSocket, char* data, int length);
	static int Bind(SOCKET serverSocket, const sockaddr* name, int namelen);
	static SOCKET Socket(int af, int type, int protocol);
	static int Listen(SOCKET s, int backlog);
	static SOCKET Accept(SOCKET serverSocket, sockaddr* addr, int* addrlen);
};

