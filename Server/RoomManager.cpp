#include "RoomManager.h"
#include "Exceptions.h"


RoomManager::RoomManager()
{
	m_rooms = std::map<int, std::unique_ptr<Room>>();
}

Room& RoomManager::getRoom(int ID)
{
	if (this->m_rooms.find(ID) == this->m_rooms.end())
	{
		throw Exception("Couldn't identify room using ID");
	}
	return *this->m_rooms[ID];
}

void RoomManager::createRoom(const unsigned int roomID, const LoggedUser lu, const RoomData rd)
{
	this->m_rooms[roomID] = std::make_unique<Room>(roomID, rd.name, rd.maxPlayers, rd.numOfQuestionsInGame, rd.timePerQuestion, RoomStatus::WAITING, std::vector<LoggedUser>() = { lu });
}


void RoomManager::deleteRoom(int ID)
{
	this->m_rooms.erase(ID);
}


RoomStatus RoomManager::getRoomState(int ID)
{
	return (*this->m_rooms[ID]).getMetadata().isActive;
}


std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (auto &it : this->m_rooms)
		rooms.push_back((*it.second).getMetadata());
	return rooms;
}
