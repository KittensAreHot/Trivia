#include "ConnectionHandler.h"
#include "Exceptions.h"
#include <iostream>


int ConnectionHandler::Send(SOCKET clientSocket, char* data, int length)
{
	int res = 0;
	res = send(clientSocket, data, length, 0);
	if (res == SOCKET_ERROR) {
		throw Exception("Couldn't send message. Error code: " + std::to_string(WSAGetLastError()));
	}
	return res;
}


int ConnectionHandler::Recv(SOCKET clientSocket, char* data, int length)
{
	int res = 0;
	res = recv(clientSocket, data, length, 0);
	if (res == SOCKET_ERROR) {
		throw Exception("Couldn't recieve message. Error code: " + std::to_string(WSAGetLastError()));
	}
	return res;
}


int ConnectionHandler::Bind(SOCKET serverSocket, const sockaddr* name, int namelen)
{
	int res = 0;
	res = bind(serverSocket, name, namelen);
	if (res == SOCKET_ERROR) {
		throw Exception("Couldn't send. Error code: " + std::to_string(WSAGetLastError()));
	}
	return res;
}


SOCKET ConnectionHandler::Socket(int af, int type, int protocol)
{
	SOCKET res = 0;
	res = socket(af, type, protocol);
	if (res == INVALID_SOCKET) {
		throw Exception("Couldn't create socket. Error code: " + std::to_string(WSAGetLastError()));
	}
	return res;
}


int ConnectionHandler::Listen(SOCKET s, int backlog)
{
	int res = 0;
	res = listen(s, backlog);
	if (res == SOCKET_ERROR) {
		throw Exception("Couldn't listen to the port. Error code: " + std::to_string(WSAGetLastError()));
	}
	return res;
}


SOCKET ConnectionHandler::Accept(SOCKET serverSocket, sockaddr* addr, int* addrlen)
{
	SOCKET res = INVALID_SOCKET;
	res = accept(serverSocket, addr, addrlen);
	if (res == INVALID_SOCKET) {
		throw Exception("User couldn't connect. Error code: " + std::to_string(WSAGetLastError()));
	}
	return res;
}
