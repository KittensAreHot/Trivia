#include "LoginManager.h"
#include "JsonResponsePacketSerializer.h"
#include "Exceptions.h"

#define SUCCESS 1
#define FAILED 0

int LoginManager::login(std::string username, std::string password)
{
	for (auto it : this->m_loggedUsers)
		// -- check if user already logged in
		if (it.getUsername() == username) return FAILED;

	if (this->m_database != nullptr &&
		this->m_database->doesPasswordMatch(username, password))
	{
		LoggedUser lu(username);
		this->m_loggedUsers.push_back(lu);
		return SUCCESS;
	}
	return FAILED;
}


int LoginManager::singup(std::string username, std::string email, std::string password)
{
	if (this->m_database != nullptr && 
		!this->m_database->doesUserExist(username))
	{
		this->m_database->addNewUser(username, email, password);
		return SUCCESS;
	}
	return FAILED;
}


int LoginManager::logout(std::string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); ++it)
	{
		if (it->getUsername() == username)
		{
			this->m_loggedUsers.erase(it);
			return SUCCESS;
		}
	}
	return FAILED;
}

LoggedUsers LoginManager::getLoggedUsers()
{
	return this->m_loggedUsers;
}


LoginManager::LoginManager(IDatabase* database)
{
	this->m_database = database;
}
