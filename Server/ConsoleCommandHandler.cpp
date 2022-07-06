#include "ConsoleCommandHandler.h"
#include <iostream>

#define EXIT "EXIT"
#define LIST "LIST"

ConsoleCommandHandler::ConsoleCommandHandler(LoginManager* loginManager)
{
	this->m_loginManager = loginManager;
}

void ConsoleCommandHandler::recieveCommands()
{
	while (true)
	{
		executeCommand(getUserCommand());
	}
}

std::string ConsoleCommandHandler::getUserCommand()
{

	std::string input;
	std::getline(std::cin, input);

	while (std::cin.fail() || std::cin.eof()) {
		std::cout << std::endl << "Invalid command..." << std::endl;
		std::cin.clear();
		std::getline(std::cin, input);
	}

	return input;
}

void ConsoleCommandHandler::executeCommand(std::string command)
{
	if (command == EXIT) {
		std::exit(EXIT_SUCCESS);
	}
	if (command == LIST) {
		LoggedUsers users = this->m_loginManager->getLoggedUsers();
		if (users.empty()) {
			std::cout << "No users are logged in" << std::endl;
		}
		else {
			for (size_t i = 0; i < users.size(); i++)
			{
				std::cout << users[i].getUsername() << std::endl; 
			}
		}
	}
}
