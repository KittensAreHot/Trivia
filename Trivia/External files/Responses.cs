using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Trivia.Pages;

namespace Client
{
    enum ResponseCode
    {
        LOGINRESPONSE = 101,
        SIGNUPRESPONSE = 102,
        ERRORRESPONSE = 103,
        SIGNOUTRESPONSE = 104,
        GETROOMSRESPONSE = 105,
        GETPLAYERSINROOMRESPONSE = 106,
        GETPERSONALSTATSRESPONSE = 107,
        GETHIGHSCORERESPONSE = 108,
        JOINROOMRESPONSE = 109,
        CREATEROOMRESPONSE = 110,
        CLOSEROOMRESPONSE = 111,
        STARTGAMERESPONSE = 112,
        GETROOMSTATERESPONSE = 113,
        LEAVEROOMRESPONSE = 114,
    }

    class LoginResponse
    {
        public int status = 0;
    }
    class SignupResponse
    {
        public int status = 0;
    }
    class ErrorResponse
    {
        public string Message = "Unspecified Error";
    }
    class LogoutResponse
    {
        public uint status = 0;
    }
    class GetRoomsResponse
    {
        public uint Status = 0;
        public List<RoomInfo> rooms = new List<RoomInfo>();
    }
    class GetPlayersInRoomResponse
    {
        public List<string> players = new List<string>();
    }
    class GetStatisticsResponse
    {
        public uint status = 0;
        public List<string> statistics = new List<string>();
    }
    class JoinRoomResponse
    {
        public uint status = 0;
    }
    class CreateRoomResponse
    {
        public uint status = 0;
    }
    class CloseRoomResponse
    {
        public uint status = 0;
    }
    class StartGameResponse
    {
        public uint status = 0;
    }
    class GetRoomStateResponse
    {
        public uint Status = 0;
        public bool GameStarted = false;
        public List<string> Players = new List<string>();
        public uint QuestionCount = 0;
        public uint TimePerQuestion = 0;
    }
    class LeaveRoomResponse
    {
        public uint status = 0;
    }

}
