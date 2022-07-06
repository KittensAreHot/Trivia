#include "Room.h"


Room::Room(unsigned int id, std::string name, unsigned int maxPlayers, unsigned int numOfQuestions, unsigned int timePerQuestion, RoomStatus isActive, std::vector<LoggedUser> roomUsers)
	: m_users(roomUsers)
{
	RoomData rd = { id, name, maxPlayers, numOfQuestions, timePerQuestion, isActive };
	m_metadata = rd;
}

RoomData& Room::getMetadata()
{
	return this->m_metadata;
}


void Room::setMetadata(RoomData rd)
{
	this->m_metadata = rd;
}


void Room::addUser(LoggedUser lu)
{
	// -- add user to room
	this->m_users.push_back(lu);
}


void Room::removeUser(LoggedUser lu)
{
	// -- delete user from room
	for (auto it = this->m_users.begin(); it != this->m_users.end(); ++it)
		if (it->getUsername() == lu.getUsername()) {
			this->m_users.erase(it);
			return;
		}
}


std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> all_users;
	for (auto &it : this->m_users)
		all_users.push_back(it.getUsername());
	return all_users;
}
