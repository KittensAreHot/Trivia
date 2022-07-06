#pragma once
#include <vector>
#include "Response.h"

typedef std::vector<unsigned char> Buffer;

class JsonResponsePacketSerializer
{
public:
	//message format
	/*
	PACKET CODE | PACKET DATA LENGTH | PACKET DATA
	*/

	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);
	static Buffer serializeResponse(const LogoutResponse& response);
	static Buffer serializeResponse(const GetRoomsResponse& response);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& response);
	static Buffer serializeResponse(const JoinRoomResponse& response);
	static Buffer serializeResponse(const CreateRoomResponse& response);
	static Buffer serializeResponse(const GetStatisticsResponse& response);
	static Buffer serializeResponse(const CloseRoomResponse& response);
	static Buffer serializeResponse(const StartGameResponse& response);
	static Buffer serializeResponse(const GetRoomStateResponse& response);
	static Buffer serializeResponse(const LeaveRoomResponse& response);

private:
	static void mountMessageToBuffer(Buffer& buff, const std::string& str);
};

