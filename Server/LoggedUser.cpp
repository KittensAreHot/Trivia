#include "LoggedUser.h"


std::string LoggedUser::getUsername() const {
	return this->m_username;
}

LoggedUser::LoggedUser(std::string username) : m_username(username) { }
