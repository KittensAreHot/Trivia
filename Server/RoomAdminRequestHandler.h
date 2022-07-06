#pragma once
#include "RoomMemberRequestHandler.h"

class RequestHandlerFactory;
class RoomMemberRequestHandler;

class RoomAdminRequestHandler :
	public RoomMemberRequestHandler
{
public:
	RoomAdminRequestHandler() = delete;
	RoomAdminRequestHandler(const RoomAdminRequestHandler&) = delete;
	RoomAdminRequestHandler& operator=(const RoomAdminRequestHandler&) = delete;

	RoomAdminRequestHandler(const Room room, const LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	~RoomAdminRequestHandler();
	virtual bool isRequestRelevant(RequestInfo reqInfo) const override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	RequestResult leaveRoom(RequestInfo) = delete; //an admin needs other logic when leaving a room ⬎
	RequestResult closeRoom(RequestInfo);
	RequestResult startGame(RequestInfo);
};

