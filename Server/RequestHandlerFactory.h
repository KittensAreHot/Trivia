#pragma once
#pragma message("Got into RequestHandlerFactory")
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include <mutex>

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler; 
class RoomAdminRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const std::string username);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const std::string username, unsigned int roomID);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const std::string username, unsigned int roomID);
	LoginManager& getLoginManager();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	std::mutex& getLoginManagerMutex();
	std::mutex& getStatisticsManagerMutex();
	std::mutex& getRoomManagerMutex();

private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	StatisticsManager m_statisticsManager;
	RoomManager m_roomManager;
	std::mutex m_loginManager_mutex;
	std::mutex m_statisticsManager_mutex;
	std::mutex m_roomManager_mutex;
};

