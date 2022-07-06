#include "MenuRequestHandler.h"
#include "Exceptions.h"
#include "JsonRequestPacketDeserializer.h"
#include <mutex>

bool MenuRequestHandler::isRequestRelevant(RequestInfo reqInfo) const
{
	return reqInfo.requestId == Prefix::SIGNOUTREQUEST ||
		reqInfo.requestId == Prefix::GETROOMSREQUEST ||
		reqInfo.requestId == Prefix::GETPLAYERSINROOMREQUEST ||
		reqInfo.requestId == Prefix::GETPERSONALSTATSREQUEST ||
		reqInfo.requestId == Prefix::GETHIGHSCOREREQUEST ||
		reqInfo.requestId == Prefix::JOINROOMREQUEST ||
		reqInfo.requestId == Prefix::CREATEROOMREQUEST;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInfo)
{
	try
	{
		if (reqInfo.requestId == Prefix::SIGNOUTREQUEST) {
			return this->signout(reqInfo);
		}
		if (reqInfo.requestId == Prefix::GETROOMSREQUEST) {
			return this->getRooms(reqInfo);
		}
		if (reqInfo.requestId == Prefix::GETPLAYERSINROOMREQUEST) {
			return this->getPlayersInRoom(reqInfo);
		}
		if (reqInfo.requestId == Prefix::GETPERSONALSTATSREQUEST) {
			return this->getPersonalStats(reqInfo);
		}
		if (reqInfo.requestId == Prefix::GETHIGHSCOREREQUEST) {
			return this->getHighScore(reqInfo);
		}
		if (reqInfo.requestId == Prefix::JOINROOMREQUEST) {
			return this->joinRoom(reqInfo);
		}
		if (reqInfo.requestId == Prefix::CREATEROOMREQUEST) {
			return this->createRoom(reqInfo);
		}
	}
	catch (...)
	{
	}
	return {
		   JsonResponsePacketSerializer::serializeResponse({ "Invalid data" }),
		   nullptr
	};
}

RequestResult MenuRequestHandler::signout(const RequestInfo ri) const
{
	std::unique_lock<std::mutex> loginManagerMutex(this->m_handlerFactory.getLoginManagerMutex());
	LogoutResponse logoutResponse = {
		static_cast<unsigned int>(this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername()))
	};
	loginManagerMutex.unlock();
	return {
		JsonResponsePacketSerializer::serializeResponse(logoutResponse),
		this->m_handlerFactory.createLoginRequestHandler() //we go back to the login state
	};
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo ri) const
{
	GetRoomsResponse rooms = {};
	std::unique_lock<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	rooms.rooms = this->m_roomManager.getRooms();
	roomManagerMutex.unlock();
	rooms.status = rooms.rooms.empty();

	return {
		JsonResponsePacketSerializer::serializeResponse(rooms),
		nullptr
	};
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo ri) const
{
	GetPlayersInRoomResponse playersInRoom = {};
	std::unique_lock<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	playersInRoom.players = this->m_roomManager.getRoom(JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(ri.buffer).roomId).getAllUsers();
	roomManagerMutex.unlock();

	return {
		JsonResponsePacketSerializer::serializeResponse(playersInRoom),
		nullptr
	};
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo ri) const
{
	GetPersonalStatsResponse personalStats = {};
	personalStats.statistics = std::vector<std::string>(); //TODO: use "this->m_statisticsManager" instead
	personalStats.status = 1;
	//std::unique_lock<std::mutex> statisticsManagerMutex(this->m_handlerFactory.getStatisticsManagerMutex());
	//statisticsManagerMutex.unlock();

	return {
		JsonResponsePacketSerializer::serializeResponse(personalStats),
		nullptr
	};
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo ri) const
{
	GetHighScoreResponse highScore = {};
	highScore.statistics = std::vector<std::string>(); //TODO: use "this->m_statisticsManager" instead
	highScore.status = 1;
	//std::unique_lock<std::mutex> statisticsManagerMutex(this->m_handlerFactory.getStatisticsManagerMutex());
	//statisticsManagerMutex.unlock();

	return {
		   JsonResponsePacketSerializer::serializeResponse(highScore),
		   nullptr
	};
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo ri)
{
	JoinRoomResponse joinRoom = {};
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(ri.buffer);
	std::unique_lock<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	Room& room = this->m_roomManager.getRoom(joinRoomRequest.roomId);

	if (room.getMetadata().isActive == RoomStatus::WAITING && room.getAllUsers().size() < room.getMetadata().maxPlayers)
	{
		this->m_isSafeDestruction = true;
		room.addUser(this->m_user);
		roomManagerMutex.unlock();
		joinRoom.status = 1;
	}
	else {
		roomManagerMutex.unlock();
		joinRoom.status = 0;
	}

	return {
		JsonResponsePacketSerializer::serializeResponse(joinRoom),
		reinterpret_cast<IRequestHandler*>(this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user.getUsername(), joinRoomRequest.roomId))
	};
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo ri)
{
	this->m_isSafeDestruction = true;
	CreateRoomResponse createRoom = {};
	CreateRoomRequest roomReqData = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(ri.buffer);
	RoomData metaData = { 0, roomReqData.roomName, roomReqData.maxUsers, roomReqData.questionCount, roomReqData.answerTimeout , RoomStatus::WAITING };
	std::lock_guard<std::mutex> roomManagerMutex(this->m_handlerFactory.getRoomManagerMutex());
	static int roomIDIter = 1;
	this->m_roomManager.createRoom(roomIDIter, this->m_user, metaData);
	roomIDIter++;
	createRoom.status = 1;

	return {
		JsonResponsePacketSerializer::serializeResponse(createRoom),
		reinterpret_cast<IRequestHandler*>(this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user.getUsername(), roomIDIter - 1))
	};
}

MenuRequestHandler::MenuRequestHandler(const LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) :
		m_user(user), m_roomManager(roomManager),
		m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{}

MenuRequestHandler::~MenuRequestHandler()
{
	if (!this->m_isSafeDestruction) {
		std::unique_lock<std::mutex> loginManagerMutex(this->m_handlerFactory.getLoginManagerMutex());
		this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
		loginManagerMutex.unlock();
	}
}
