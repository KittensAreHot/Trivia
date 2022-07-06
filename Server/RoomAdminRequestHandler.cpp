#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(const Room room, const LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory)
			: RoomMemberRequestHandler(room, user, roomManager, handlerFactory) //as the default constructor is deleted we must provide which constructor we use to essentially inherit the class
{}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
	if (!this->m_isSafeDestruction) {
		this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
	}
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo reqInfo) const
{
	return	reqInfo.requestId == Prefix::CLOSEROOMREQUEST ||
		reqInfo.requestId == Prefix::STARTGAMEREQUEST ||
		reqInfo.requestId == Prefix::GETROOMSTATEREQUEST;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo reqInfo)
{
	try
	{
		if (reqInfo.requestId == Prefix::CLOSEROOMREQUEST) {
			return this->closeRoom(reqInfo);
		}
		if (reqInfo.requestId == Prefix::STARTGAMEREQUEST) {
			return this->startGame(reqInfo);
		}
		if (reqInfo.requestId == Prefix::GETROOMSTATEREQUEST) {
			return this->getRoomState(reqInfo);
		}
	}
	catch (...)
	{}
	return {
		   JsonResponsePacketSerializer::serializeResponse({ "Invalid data" }),
		   nullptr
	};
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo)
{
	CloseRoomResponse closeRoom = {};
	
	std::unique_lock<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	this->m_roomManager.getRoom(m_room.getMetadata().id).getMetadata().isActive = RoomStatus::CLOSING;
	roomManagerMutex.unlock();

	closeRoom.status = 1;

	return {
		JsonResponsePacketSerializer::serializeResponse(closeRoom),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername()) //TODO: finish it up
	};
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo)
{
	StartGameResponse startGame = {};

	std::unique_lock<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	this->m_roomManager.getRoom(m_room.getMetadata().id).getMetadata().isActive = RoomStatus::CLOSING;
	roomManagerMutex.unlock();

	startGame.status = 1;

	return {
		JsonResponsePacketSerializer::serializeResponse(startGame),
		nullptr //TODO: actual game
	};
}
