#include "RequestHandlerFactory.h"
#include "RoomMemberRequestHandler.h"	// The files have to be included here as to allow them to be defined correctly, for details: https://stackoverflow.com/a/72736706/1233652
#include "RoomAdminRequestHandler.h"	// ────────────────────────────────────────────────────┘

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
 : m_loginManager(database), m_roomManager(), m_statisticsManager(),
	m_roomManager_mutex(), m_statisticsManager_mutex(), m_loginManager_mutex()
{
	this->m_database = database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this->m_loginManager, *this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const std::string username)
{
	return new MenuRequestHandler(LoggedUser(username), this->m_roomManager, this->m_statisticsManager, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const std::string username, unsigned int roomID)
{
	return new RoomMemberRequestHandler(this->m_roomManager.getRoom(roomID), LoggedUser(username), this->m_roomManager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const std::string username, unsigned int roomID)
{
	return new RoomAdminRequestHandler(this->m_roomManager.getRoom(roomID), LoggedUser(username), this->m_roomManager, *this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

std::mutex& RequestHandlerFactory::getLoginManagerMutex()
{
	return this->m_loginManager_mutex;
}

std::mutex& RequestHandlerFactory::getStatisticsManagerMutex()
{
	return this->m_statisticsManager_mutex;
}

std::mutex& RequestHandlerFactory::getRoomManagerMutex()
{
	return this->m_roomManager_mutex;
}
