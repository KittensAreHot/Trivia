#pragma once
#include <map>
#include "Room.h"
#include <memory>


class RoomManager {
private:
	std::map<int, std::unique_ptr<Room>> m_rooms;
public:
	RoomManager();
	Room& getRoom(const int ID);
	void createRoom(const unsigned int roomID, LoggedUser lu, RoomData rd);
	void deleteRoom(int ID);
	RoomStatus getRoomState(int ID);
	std::vector<RoomData> getRooms();
};
