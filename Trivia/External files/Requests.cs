using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    enum RequestCode
    {
        LOGINREQUEST = 51,
        SIGNUPREQUEST = 52,
        SIGNOUTREQUEST = 53,
        GETROOMSREQUEST = 54,
        GETPLAYERSINROOMREQUEST = 55,
        GETPERSONALSTATSREQUEST = 56,
        GETHIGHSCOREREQUEST = 57,
        JOINROOMREQUEST = 58,
        CREATEROOMREQUEST = 59,
        CLOSEROOMREQUEST = 60,
        STARTGAMEREQUEST = 61,
        GETROOMSTATEREQUEST = 62,
        LEAVEROOMREQUEST = 63,
    }

    class LoginRequest
    {
        public readonly string username;
        public readonly string password;

        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }
    }
    class SignupRequest
    {
        public readonly string username;
        public readonly string email;
        public readonly string password;

        public SignupRequest(string username, string email, string password)
        {
            this.username = username;
            this.email = email;
            this.password = password;
        }
    }
    class SignoutRequest
    {
    }
    class GetRoomsRequest
    {

    }
    class GetPersonalStatsRequest
    {

    }
    class GetHighScoreRequest
    {

    }
    class GetPlayersInRoomRequest
    {
        public uint roomId;

        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    class JoinRoomRequest
    {
        public uint roomId;

        public JoinRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    class CreateRoomRequest
    {
        public string roomName;
        public uint maxUsers;
        public uint questionCount;
        public uint answerTimeout;

        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
        }
    }
    class CloseRoomRequest
    {

    }
    class StartGameRequest
    {

    }
    class GetRoomStateRequest
    {

    }
    class LeaveRoomRequest
    {

    }

}
