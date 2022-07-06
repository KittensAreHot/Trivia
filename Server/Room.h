#pragma once
#include <string>
#include <vector>
#include "LoggedUser.h"


enum class RoomStatus
{
	WAITING = 0,
	PLAYING = 1,
	CLOSING = 2,
};

typedef struct RoomData {
	unsigned int id{};
	std::string name{};
	unsigned int maxPlayers{};
	unsigned int numOfQuestionsInGame{};
	unsigned int timePerQuestion{};
	RoomStatus isActive = RoomStatus::WAITING;
} RoomData;

class Room {
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	// getters & setters
	Room(unsigned int id, std::string name, unsigned int maxPlayer, unsigned int numOfQuestions, unsigned int timePerQuestion, RoomStatus isActive, std::vector<LoggedUser> roomUsers);
	RoomData& getMetadata();
	void setMetadata(RoomData rd);
	// methods
	void addUser(LoggedUser lu);
	void removeUser(LoggedUser lu);
	std::vector<std::string> getAllUsers();
};
