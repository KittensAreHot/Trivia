#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"


class RoomMemberRequestHandler :
    public IRequestHandler
{
public:
	RoomMemberRequestHandler() = delete;
	RoomMemberRequestHandler(const RoomMemberRequestHandler&) = delete;
	RoomMemberRequestHandler& operator=(const RoomMemberRequestHandler&) = delete;

	RoomMemberRequestHandler(const Room room, const LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	~RoomMemberRequestHandler();
	virtual bool isRequestRelevant(RequestInfo reqInfo) const override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

protected:

	RequestResult leaveRoom(RequestInfo);
	RequestResult getRoomState(RequestInfo);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	bool m_isSafeDestruction = false; //determines whether we need to delete the user data or not
};

class RequestHandlerFactory;

