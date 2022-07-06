#include "JsonResponsePacketSerializer.h"
#include "JsonParser/json.hpp"
#include "Prefixes.h"

using json = nlohmann::json;

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer responseBuff;
    json j;

    j["Message"] = response.Message;
    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::ERRORRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    Buffer responseBuff;
    json j;

    j["Status"] = response.status;
    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::LOGINRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    Buffer responseBuff;
    json j;

    j["Status"] = response.status;
    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::SIGNUPRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);
    
    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
    Buffer responseBuff;
    json j;

    j["Status"] = response.status;
    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::SIGNOUTRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);
    
    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;
    j["rooms"] = json::array();

    for (size_t i = 0; i < response.rooms.size(); i++)
    {
        json roomEntity = json::object();
        roomEntity["ID"] = response.rooms[i].id;
        roomEntity["Active"] = response.rooms[i].isActive;
        roomEntity["MaxPlayers"] = response.rooms[i].maxPlayers;
        roomEntity["Name"] = response.rooms[i].name;
        roomEntity["NumberOfQuestions"] = response.rooms[i].numOfQuestionsInGame;
        roomEntity["QuestionTime"] = response.rooms[i].timePerQuestion;

        j["rooms"].push_back(roomEntity);
    }

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::GETROOMSRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
    Buffer responseBuff;
    json j;
    j["players"] = json::array();

    for (size_t i = 0; i < response.players.size(); i++)
    {
        j["players"].push_back(response.players[i]);
    }

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::GETPLAYERSINROOMRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::JOINROOMRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::CREATEROOMRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetStatisticsResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;
    j["statistics"] = json::array();

    for (size_t i = 0; i < response.statistics.size(); i++)
    {
        j["statistics"].push_back(response.statistics[i]);
    }

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::GETPERSONALSTATSRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::CLOSEROOMRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::STARTGAMERESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;
    j["GameStarted"] = response.hasGameBegun;
    j["Players"] = response.players;
    j["QuestionCount"] = response.questionCount;
    j["TimePerQuestion"] = response.answerTimeout;

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::GETROOMSTATERESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
    Buffer responseBuff;
    json j;
    j["Status"] = response.status;

    std::string jDump = j.dump();
    responseBuff.push_back(static_cast<char>(Prefix::LEAVEROOMRESPONSE));
    mountMessageToBuffer(responseBuff, jDump);

    return responseBuff;
}


void JsonResponsePacketSerializer::mountMessageToBuffer(Buffer& buff, const std::string& str)
{
    size_t messageLen = str.length();
    buff.insert(buff.end(), reinterpret_cast<char*>(&messageLen), reinterpret_cast<char*>(&messageLen) + sizeof(int));
    buff.insert(buff.end(), str.begin(), str.end());
}
