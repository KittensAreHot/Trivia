#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

typedef std::vector<LoggedUser> LoggedUsers;

class LoginManager
{
public:
	LoginManager(IDatabase* database);
	int singup(std::string username, std::string email, std::string password);
	int login(std::string username, std::string password);
	int logout(std::string username);
	LoggedUsers getLoggedUsers();

private:
	IDatabase* m_database;
	LoggedUsers m_loggedUsers;
};
