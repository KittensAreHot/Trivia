using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Windows;
using Trivia.Pages; 

namespace Client
{
    static class Client
    {
        public static bool StartClient()
        {
            try
            {
                clientSocket = new TcpClient();

                IAsyncResult result = clientSocket.BeginConnect(ip, port, null, null);

                // give the client 5 seconds to connect
                result.AsyncWaitHandle.WaitOne(5000);

                if (!clientSocket.Connected)
                {
                    clientSocket.EndConnect(result);
                }

                clientStream = clientSocket.GetStream();
            }
            catch (SocketException)
            {
                MessageBox.Show("Connection failed",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Hand);
                return false;
            }
            return true;
        }

        public static void CloseConnection()
        {
            clientStream.Close();
            if (clientSocket.Connected)
            {
                clientSocket.Close();
            }
        }

        public static bool IsConnected()
        {
            if (clientSocket == null)
            {
                return false;
            }
            return clientSocket.Connected;
        }

        public static bool Login(string username, string password)
        {
            if (IsConnected() == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new LoginRequest(username, password));
            Client.username = username;
            return ReadMsg() is LoginResponse response && response.status == 1;
        }
        public static bool Signup(string username, string email, string password)
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new SignupRequest(username, email, password));

            Client.username = username;
            return ReadMsg() is SignupResponse response && response.status == 1;
        }
        public static bool Signout(){
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new SignoutRequest());

            return ReadMsg() is LogoutResponse response && response.status == 1;
        }
        public static List<RoomInfo> GetRooms()
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return new List<RoomInfo>();
            }
            SendMsg(new GetRoomsRequest());

            return !(ReadMsg() is GetRoomsResponse response)
                ? new List<RoomInfo>()
                : response.Status == 0 ? response.rooms : new List<RoomInfo>();
        }
        public static List<string> GetPlayersInRoom(uint roomID){
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return new List<string>();
            }
            SendMsg(new GetPlayersInRoomRequest(roomID));

            return !(ReadMsg() is GetPlayersInRoomResponse response) ? new List<string>() : response.players;
        }
        public static List<Statistics> GetPersonalStats()
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return new List<Statistics>();
            }
            SendMsg(new GetPersonalStatsRequest());

            if (!(ReadMsg() is GetStatisticsResponse response))
            {
                return new List<Statistics>();
            }
            List<Statistics> personalStatistics = new List<Statistics>();
            if (response.status == 1)
            {
                for (int i = 0; i < response.statistics.Count; i++)
                {
                    personalStatistics.Add(JsonConvert.DeserializeObject<Statistics>(response.statistics[i]));
                }
            }
            return personalStatistics;
        }
        public static List<Statistics> GetHighScore(){
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return new List<Statistics>();
            }
            SendMsg(new GetHighScoreRequest());

            if (!(ReadMsg() is GetStatisticsResponse response))
            {
                return new List<Statistics>();
            }
            List<Statistics> bestStatistics = new List<Statistics>();
            if (response.status == 1)
            {
                for (int i = 0; i < response.statistics.Count; i++)
                {
                    bestStatistics.Add(JsonConvert.DeserializeObject<Statistics>(response.statistics[i]));
                }
            }
            return bestStatistics;
        }
        public static bool JoinRoom(uint roomID){
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new JoinRoomRequest(roomID));

            return ReadMsg() is JoinRoomResponse response && response.status == 1;
        }
        public static bool CreateRoom(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new CreateRoomRequest(roomName, maxUsers, questionCount, answerTimeout));

            return ReadMsg() is CreateRoomResponse response && response.status == 1;
        }
        public static bool LeaveRoom(){
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new LeaveRoomRequest());

            return ReadMsg() is LeaveRoomResponse response && response.status == 1;
        }
        public static bool CloseRoom()
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new CloseRoomRequest());

            return ReadMsg() is CloseRoomResponse response && response.status == 1;
        }
        public static bool StartRoom()
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return false;
            }
            SendMsg(new CloseRoomRequest());

            return ReadMsg() is CloseRoomResponse response && response.status == 1;
        }


        public static GetRoomStateResponse GetRoomState()
        {
            if (clientSocket.Connected == false)
            {
                MessageBox.Show("Couldn't connect to server",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return null;
            }
            SendMsg(new GetRoomStateRequest());

            return (ReadMsg() is GetRoomStateResponse response) ? response : null;
        }


        private static void SendMsg(object request)
        {
            try
            {
                string finalMsg = Convert.ToChar(GetCode(request)).ToString();
                if (finalMsg == "255")
                {
                    MessageBox.Show("Incorrect message code",
                                    "Server error",
                                    MessageBoxButton.OK,
                                    MessageBoxImage.Error);
                }
                string jsonReq = JsonConvert.SerializeObject(request, Formatting.Indented);
                for (int i = 0; i < 4; i++)
                {
                    finalMsg += Convert.ToChar(BitConverter.GetBytes(jsonReq.Length)[i]).ToString();
                }
                finalMsg += jsonReq;

                clientStream.Write(Encoding.ASCII.GetBytes(finalMsg), 0, finalMsg.Length);
            }
            catch (System.IO.IOException)
            {
                    MessageBox.Show("Server Connection Lost",
                                    "Server error",
                                    MessageBoxButton.OK,
                                    MessageBoxImage.Error);
            }
        }
        private static object ReadMsg()
        {
            try
            {
                byte[] msgByte = new byte[1028];
                string msg = "";
                Type responseType;

                if (clientStream.Read(msgByte, 0, 1) != 1)
                {
                    MessageBox.Show("Didn't receive code",
                                    "Server error",
                                    MessageBoxButton.OK,
                                    MessageBoxImage.Error);
                    return null;
                }
                responseType = CodeToType(msgByte[0]);
                if (responseType == null)
                {
                    MessageBox.Show("Received incorrect code",
                                    "Server error",
                                    MessageBoxButton.OK,
                                    MessageBoxImage.Error);
                    return null;
                }
                if (clientStream.Read(msgByte, 0, 4) != 4) //no offset because the code is now redundent
                {
                    MessageBox.Show("Didn't receive length",
                                    "Server error",
                                    MessageBoxButton.OK,
                                    MessageBoxImage.Error);
                    return null;
                }
                int msgLen = BitConverter.ToInt32(msgByte, 0);
                int readData = 0;
                while (readData != msgLen)
                {
                    int currentRead = clientStream.Read(msgByte, 0, msgByte.Length);
                    if (currentRead == 0)
                    {
                        MessageBox.Show("Got an incorrect length",
                                        "Server error",
                                        MessageBoxButton.OK,
                                        MessageBoxImage.Error);
                        return null;
                    }
                    readData += currentRead;
                    msg += Encoding.ASCII.GetString(msgByte);
                }
                if (responseType == typeof(ErrorResponse))
                {
                    ErrorResponse err = JsonConvert.DeserializeObject<ErrorResponse>(msg);
                    MessageBox.Show("Got an error: " + Environment.NewLine + err.Message,
                                    "Server error",
                                    MessageBoxButton.OK,
                                    MessageBoxImage.Warning);
                    CloseConnection();
                    return null;
                }

                return ConvertToType(responseType, msg);
            }
            catch (System.IO.IOException)
            {
                MessageBox.Show("Server Connection Lost",
                                "Server error",
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
            }
            return null;
        }
        private static object ConvertToType(Type type, string msg)
        {
            if (type == typeof(LoginResponse))
            {
                return JsonConvert.DeserializeObject<LoginResponse>(msg);
            }
            else if (type == typeof(SignupResponse))
            {
                return JsonConvert.DeserializeObject<SignupResponse>(msg);
            }
            else if (type == typeof(LogoutResponse))
            {
                return JsonConvert.DeserializeObject<LogoutResponse>(msg);
            }
            else if (type == typeof(GetRoomsResponse))
            {
                return JsonConvert.DeserializeObject<GetRoomsResponse>(msg);
            }
            else if (type == typeof(GetPlayersInRoomResponse))
            {
                return JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(msg);
            }
            else if (type == typeof(GetStatisticsResponse))
            {
                return JsonConvert.DeserializeObject<GetStatisticsResponse>(msg);
            }
            else if (type == typeof(JoinRoomResponse))
            {
                return JsonConvert.DeserializeObject<JoinRoomResponse>(msg);
            }
            else if (type == typeof(CreateRoomResponse))
            {
                return JsonConvert.DeserializeObject<CreateRoomResponse>(msg);
            }
            else if (type == typeof(CloseRoomResponse))
            {
                return JsonConvert.DeserializeObject<CloseRoomResponse>(msg);
            }
            else if (type == typeof(StartGameResponse))
            {
                return JsonConvert.DeserializeObject<StartGameResponse>(msg);
            }
            else if (type == typeof(GetRoomStateResponse))
            {
                return JsonConvert.DeserializeObject<GetRoomStateResponse>(msg);
            }
            else if (type == typeof(LeaveRoomResponse))
            {
                return JsonConvert.DeserializeObject<LeaveRoomResponse>(msg);
            }
            else
            {
                return null;
            }
        }

        private static byte GetCode(object request)
        {
            if (request.GetType() == typeof(LoginRequest))
            {
                return (byte)RequestCode.LOGINREQUEST;
            }
            else if (request.GetType() == typeof(SignupRequest))
            {
                return (byte)RequestCode.SIGNUPREQUEST;
            }
            else if (request.GetType() == typeof(SignoutRequest))
            {
                return (byte)RequestCode.SIGNOUTREQUEST;
            }
            else if (request.GetType() == typeof(GetRoomsRequest))
            {
                return (byte)RequestCode.GETROOMSREQUEST;
            }
            else if (request.GetType() == typeof(GetPlayersInRoomRequest))
            {
                return (byte)RequestCode.GETPLAYERSINROOMREQUEST;
            }
            else if (request.GetType() == typeof(GetPersonalStatsRequest))
            {
                return (byte)RequestCode.GETPERSONALSTATSREQUEST;
            }
            else if (request.GetType() == typeof(GetHighScoreRequest))
            {
                return (byte)RequestCode.GETHIGHSCOREREQUEST;
            }
            else if (request.GetType() == typeof(JoinRoomRequest))
            {
                return (byte)RequestCode.JOINROOMREQUEST;
            }
            else if (request.GetType() == typeof(CreateRoomRequest))
            {
                return (byte)RequestCode.CREATEROOMREQUEST;
            }
            else if (request.GetType() == typeof(CloseRoomRequest))
            {
                return (byte)RequestCode.CLOSEROOMREQUEST;
            }
            else if (request.GetType() == typeof(StartGameRequest))
            {
                return (byte)RequestCode.STARTGAMEREQUEST;
            }
            else if (request.GetType() == typeof(GetRoomStateRequest))
            {
                return (byte)RequestCode.GETROOMSTATEREQUEST;
            }
            else if (request.GetType() == typeof(LeaveRoomRequest))
            {
                return (byte)RequestCode.LEAVEROOMREQUEST;
            }

            return 255;
        }

        private static Type CodeToType(byte code)
        {
            switch (code)
            {
                case (byte)ResponseCode.LOGINRESPONSE:
                    return typeof(LoginResponse);

                case (byte)ResponseCode.SIGNUPRESPONSE:
                    return typeof(SignupResponse);

                case (byte)ResponseCode.ERRORRESPONSE:
                    return typeof(ErrorResponse);

                case (byte)ResponseCode.SIGNOUTRESPONSE:
                    return typeof(LogoutResponse);

                case (byte)ResponseCode.GETROOMSRESPONSE:
                    return typeof(GetRoomsResponse);

                case (byte)ResponseCode.GETPLAYERSINROOMRESPONSE:
                    return typeof(GetPlayersInRoomResponse);

                case (byte)ResponseCode.GETPERSONALSTATSRESPONSE:
                    return typeof(GetStatisticsResponse);

                case (byte)ResponseCode.GETHIGHSCORERESPONSE:
                    return typeof(GetStatisticsResponse);

                case (byte)ResponseCode.JOINROOMRESPONSE:
                    return typeof(JoinRoomResponse);

                case (byte)ResponseCode.CREATEROOMRESPONSE:
                    return typeof(CreateRoomResponse);

                case (byte)ResponseCode.CLOSEROOMRESPONSE:
                    return typeof(CloseRoomResponse);

                case (byte)ResponseCode.STARTGAMERESPONSE:
                    return typeof(JoinRoomResponse);

                case (byte)ResponseCode.GETROOMSTATERESPONSE:
                    return typeof(GetRoomStateResponse);

                case (byte)ResponseCode.LEAVEROOMRESPONSE:
                    return typeof(LeaveRoomResponse);

                default:
                    return null;
            }
        }

        private static TcpClient clientSocket;
        private static NetworkStream clientStream;
        private const string ip = "localhost";
        private const int port = 25634;
        static public string username = "";
    }
}
