#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <mutex>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
//CONFIGURATION
#define PORT 25634


class Communicator
{
public:
	Communicator(RequestHandlerFactory& requestHandlerFactory);
	~Communicator();
	void startHandleRequests();

private:

	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	static Buffer stringToBuffer(const char* from);
	static std::string bufferToString(const Buffer from);

	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
	RequestHandlerFactory& m_handleFactory;
};

