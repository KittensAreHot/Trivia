#include "RoomMemberRequestHandler.h"


RoomMemberRequestHandler::RoomMemberRequestHandler(const Room room, const LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
	if (!this->m_isSafeDestruction) {
		std::unique_lock<std::mutex> loginManagerMutex(this->m_handlerFactory.getLoginManagerMutex());
		this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
		loginManagerMutex.unlock();
	}
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo reqInfo) const
{
	return	reqInfo.requestId == Prefix::LEAVEROOMREQUEST ||
			reqInfo.requestId == Prefix::GETROOMSTATEREQUEST;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo reqInfo)
{
	try
	{
		if (reqInfo.requestId == Prefix::LEAVEROOMREQUEST) {
			return this->leaveRoom(reqInfo);
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo)
{
	LeaveRoomResponse leaveRoom = {};

	std::unique_lock<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	this->m_roomManager.getRoom(m_room.getMetadata().id).removeUser(this->m_user);
	roomManagerMutex.unlock();

	leaveRoom.status = 1;

	return {
		JsonResponsePacketSerializer::serializeResponse(leaveRoom),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername()) //TODO: finish it up
	};
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo)
{
	GetRoomStateResponse getRoomState = {};

	//should try to make is so you can wait until the data changes with notifications(condition var)
	std::lock_guard<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	this->m_room = this->m_roomManager.getRoom(m_room.getMetadata().id);
	getRoomState.answerTimeout = this->m_room.getMetadata().timePerQuestion;
	getRoomState.hasGameBegun = this->m_room.getMetadata().isActive == RoomStatus::PLAYING;
	getRoomState.players = this->m_room.getAllUsers();
	getRoomState.questionCount = this->m_room.getMetadata().numOfQuestionsInGame;
	getRoomState.status = this->m_room.getMetadata().isActive == RoomStatus::CLOSING;
	
	return {
		JsonResponsePacketSerializer::serializeResponse(getRoomState),
		nullptr
	};
}
