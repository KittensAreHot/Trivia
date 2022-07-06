#include "JsonRequestPacketDeserializer.h"
#include "JsonParser/json.hpp"

using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer buffer)
{
	LoginRequest ret;
    auto data = json::parse(buffer);

    ret.password = data["password"];
    ret.username = data["username"];
    return ret;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer buffer)
{
    SignupRequest ret;
    auto data = json::parse(buffer);

    ret.password = data["password"];
    ret.username = data["username"];
    ret.email = data["email"];
    return ret;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const Buffer buffer)
{
    GetPlayersInRoomRequest ret{};
    auto data = json::parse(buffer);

    ret.roomId = data["roomId"];
    
    return ret;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const Buffer buffer)
{
    JoinRoomRequest ret{};
    auto data = json::parse(buffer);

    ret.roomId = data["roomId"];

    return ret;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const Buffer buffer)
{
    CreateRoomRequest ret{};
    auto data = json::parse(buffer);

    ret.roomName = data["roomName"];
    ret.maxUsers = data["maxUsers"];
    ret.questionCount = data["questionCount"];
    ret.answerTimeout = data["answerTimeout"];

    return ret;
}
