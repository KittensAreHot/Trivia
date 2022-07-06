#pragma once
#include <string>
#include "LoginManager.h"

class ConsoleCommandHandler
{
public:
	ConsoleCommandHandler(LoginManager* loginManager);

	void recieveCommands();
	std::string getUserCommand();
	void executeCommand(std::string command);

private:
	LoginManager* m_loginManager;
};

