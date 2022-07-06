using System.Collections.Generic;

namespace Trivia.Pages
{
    public class RoomInfo
    {

        public uint ID;
        public bool Active;
        public uint MaxPlayers;
        public string Name;
        public uint NumberOfQuestions;
        public uint QuestionTime;
        
        private List<string> playerList = new List<string>();
        public List<string> PlayerList { get => playerList; set => playerList = value; }
        
        private readonly bool isOwner = false;
        public bool IsOwner { get => isOwner;}


        public RoomInfo(uint id, string name, uint maxPlayers, uint numOfQuestionsInGame, uint timePerQuestion, bool isActive, List<string> playerList, bool isOwner)
        {
            this.ID = id;
            this.Name = name;
            this.MaxPlayers = maxPlayers;
            this.NumberOfQuestions = numOfQuestionsInGame;
            this.QuestionTime = timePerQuestion;
            this.Active = isActive;
            this.playerList = playerList;
            this.isOwner = isOwner;
        }

    }
}