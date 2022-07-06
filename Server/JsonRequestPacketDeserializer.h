#pragma once
#include <vector>
#include "Request.h"


class JsonRequestPacketDeserializer
{
public:
	//message format
	/*
	PACKET CODE | PACKET DATA LENGTH | PACKET DATA
	*/

	static LoginRequest deserializeLoginRequest(const Buffer buffer);
	static SignupRequest deserializeSignupRequest(const Buffer buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const Buffer buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const Buffer buffer);
};

