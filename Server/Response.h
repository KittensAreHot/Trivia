#include <string>
#include <vector>
#include "Room.h"

typedef struct LoginResponse {
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse {
	std::string Message;
} ErrorResponse;

typedef struct LogoutResponse{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct GetStatisticsResponse{
	unsigned int status;
	std::vector<std::string> statistics;
} GetStatisticsResponse;

typedef GetStatisticsResponse GetHighScoreResponse;
typedef GetStatisticsResponse GetPersonalStatsResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse{
	unsigned int status;
} CreateRoomResponse;

typedef struct CloseRoomResponse{
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse{
	unsigned int status;
} StartGameResponse;


typedef struct GetRoomStateResponse{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;


typedef struct LeaveRoomResponse {
	unsigned int status;
} LeaveRoomResponse;
