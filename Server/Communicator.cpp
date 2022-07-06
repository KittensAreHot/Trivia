#include "Communicator.h"
#include "ConnectionHandler.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "Exceptions.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "Prefixes.h"

#define MAX_RESPONSE_LENGTH 1024

Communicator::Communicator(RequestHandlerFactory& requestHandlerFactory) : m_handleFactory(requestHandlerFactory){
	m_serverSocket = ConnectionHandler::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Communicator::~Communicator()
{
	try
	{
		for (auto& element : this->m_clients) {
			if (element.second) {
				delete element.second;
			}
		}
		if (closesocket(m_serverSocket) == SOCKET_ERROR)
		{
			throw Exception("Couldn't close the socket with the user" + std::to_string(WSAGetLastError()));
		}
	}
	catch (Exception& e) {
		std::cout << e.what();
	}
}

void Communicator::startHandleRequests()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	ConnectionHandler::Bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa));

	// Start listening for incoming requests of clients
	ConnectionHandler::Listen(m_serverSocket, SOMAXCONN);
	std::cout << "Listening on port " << PORT << std::endl;

	// Listen for connections...
	try
	{
		while (true) {
			this->bindAndListen();
		}
	}
	catch (Exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}


void Communicator::bindAndListen()
{
	SOCKET clientSocket = ConnectionHandler::Accept(m_serverSocket, NULL, NULL);
	
	std::cout << "Client accepted. Server and client can speak" << std::endl;
	this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket, this->m_handleFactory.createLoginRequestHandler()));
	std::thread(&Communicator::handleNewClient, this, clientSocket).detach();
}


void Communicator::handleNewClient(SOCKET clientSocket)
{
	try //we want to keep the server alive even when theres an error with a user/he leaves
	{
		while (true)
		{
			char msgCode;
			char data[MAX_RESPONSE_LENGTH] = { 0 };
			RequestInfo ri = { static_cast<Prefix>(0), std::time(nullptr), Buffer() }; // "general serialization"
			ConnectionHandler::Recv(clientSocket, &msgCode, sizeof(char));
			ri.requestId = static_cast<Prefix>(msgCode);
			//is a valid request?
			if (!this->m_clients[clientSocket]->isRequestRelevant(ri))
			{
				ErrorResponse err = { "Request is irrelevant" };
				Buffer response = JsonResponsePacketSerializer::serializeResponse(err);
				ConnectionHandler::Send(clientSocket, reinterpret_cast<char*>(response.data()), static_cast<int>(response.size()));
				throw Exception("User's request is irrelevant");
			}
			//can the length be used?
			int messageLength = 0;
			if (ConnectionHandler::Recv(clientSocket, reinterpret_cast<char*>(&messageLength), sizeof(int)) != sizeof(int) || messageLength > MAX_RESPONSE_LENGTH) { //read length the same way we wrote it in the serializer
				ErrorResponse err = { "Invalid packet length" };
				Buffer response = JsonResponsePacketSerializer::serializeResponse(err);
				ConnectionHandler::Send(clientSocket, reinterpret_cast<char*>(response.data()), static_cast<int>(response.size()));
				throw Exception("User gave invalid packet length");
			}
			//is the length correct?
			if (ConnectionHandler::Recv(clientSocket, data, messageLength) != messageLength) {
				ErrorResponse err = { "Length doesn't match" };
				Buffer response = JsonResponsePacketSerializer::serializeResponse(err);
				ConnectionHandler::Send(clientSocket, reinterpret_cast<char*>(response.data()), static_cast<int>(response.size()));
				throw Exception("Given length doesn't match");
			}

			//process the request
			Buffer buff = stringToBuffer(data);
			ri.buffer = buff;
			RequestResult res = this->m_clients[clientSocket]->handleRequest(ri);

			ConnectionHandler::Send(clientSocket, reinterpret_cast<char*>(res.response.data()), static_cast<int>(res.response.size()));
			if (res.newHandler) {
				delete this->m_clients[clientSocket];
				this->m_clients[clientSocket] = res.newHandler;
			}
		}
	}
	catch (...)
	{
		std::cout << "Socket " << clientSocket << " has disconnected" << std::endl;
		delete this->m_clients[clientSocket];
	}
}



Buffer Communicator::stringToBuffer(const char* from) {
	Buffer buffer;
	for (size_t i = 0; i < strlen(from + 5) + 5; i++)
		buffer.push_back(from[i]);
	return buffer;
}


std::string Communicator::bufferToString(const Buffer from) {
	std::string to;
	for (size_t i = 0; i < from.size(); i++)
		to += from[0];
	return to;
}
