#pragma once

#include <ctime>
#include <string>
#include "JsonResponsePacketSerializer.h"
#include "Prefixes.h"

typedef struct RequestInfo {
	Prefix requestId;
	std::time_t receivalTime;
	Buffer buffer;
} RequestInfo;


typedef struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;


typedef struct LoginRequest {
	std::string username;
	std::string password;
} LoginRequest;


typedef struct GetPlayersInRoomRequest {
	unsigned int roomId;
} GetPlayersInRoomRequest;


typedef struct JoinRoomRequest{
	unsigned int roomId;
} JoinRoomRequest;


typedef struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;
