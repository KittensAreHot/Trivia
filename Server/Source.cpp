#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "ConsoleCommandHandler.h"
#include "Server.h"
#include <iostream>
#include <exception>

int main()
{
	WSAInitializer wsaInit;
	Server myServer;
	myServer.run();
	ConsoleCommandHandler Console(myServer.getLoginManager());
	Console.recieveCommands();
	return 0;
}