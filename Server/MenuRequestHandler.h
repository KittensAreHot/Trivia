#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"


class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = delete;
	MenuRequestHandler(const MenuRequestHandler&) = delete;
	MenuRequestHandler& operator=(const MenuRequestHandler&) = delete;

	MenuRequestHandler(const LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory);
	~MenuRequestHandler();
	bool isRequestRelevant(RequestInfo reqInfo) const override;
	RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	RequestResult signout(const RequestInfo ri) const;
	RequestResult getRooms(const RequestInfo ri) const;
	RequestResult getPlayersInRoom(const RequestInfo ri) const;
	RequestResult getPersonalStats(const RequestInfo ri) const;
	RequestResult getHighScore(const RequestInfo ri) const;
	RequestResult joinRoom(const RequestInfo ri);
	RequestResult createRoom(const RequestInfo ri);

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

//public:
//	bool isRequestRelevant(RequestInfo ri);
//	RequestResult handleRequest(RequestInfo ri);
//	RequestResult signout(RequestInfo ri);
//	RequestResult getRooms(RequestInfo ri);
//	RequestResult getPlayersInRoom(RequestInfo ri);
//	RequestResult getPersonalStats(RequestInfo ri);
//	RequestResult getHighScore(RequestInfo ri);
//	RequestResult joinRoom(RequestInfo ri);
//	RequestResult createRoom(RequestInfo ri);
	bool m_isSafeDestruction = false; //determines whether we need to delete the user data or not
};
