using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client.Code
{
    public sealed class User
    {
        public static volatile User instance;
        private static object syncRoot = new Object();

        //fields
        private string username;
        private float avgTimeForAnswer;
        private int rightAnswers;
        private int totalAnswers;
        private int gamesPlayed;
        private int points;
        private bool isRoomAdmin;
        private RoomData room;

        private User(string username)
        {
            this.username = username;
            this.avgTimeForAnswer = 0;
            this.rightAnswers = 0;
            this.totalAnswers = 0;
            this.gamesPlayed = 0;
            this.points = 0;
            this.isRoomAdmin = false;
            this.room = new RoomData();
        }
        public static User Instance(string username = "")
        {
            if (instance == null || username != "")
            {
                lock (syncRoot)
                {
                    if (instance == null || username != "")
                        instance = new User(username);
                }
            }

            return instance;
        }
        public string GetUsername()
        { 
            return username; 
        }
        public float GetAvgTimeForAnswer()
            { return avgTimeForAnswer; }
        public int GetRightAnswers()
            { return rightAnswers; }
        public int GetTotalAnswers()
        { return totalAnswers; }
        public int GetGamesPlayed()
            { return gamesPlayed; }
        public int GetPoints()
            { return points; }
        public bool GetIsRoomAdmin()
        {
            return isRoomAdmin;
        }
        public RoomData GetRoom()
        {
            return room;
        }
        public void setAvgTimeForAnswer(float avgTime)
            { this.avgTimeForAnswer = avgTime; }
        public void setRightAnswers(int rightAnswers)
            { this.rightAnswers = rightAnswers; }
        public void setTotalAnswers(int totalAnswers)
            { this.totalAnswers = totalAnswers; }
        public void setGamesPlayed(int gamesPlayed)
            { this.gamesPlayed = gamesPlayed; }
        public void setPoints(int points)
            { this.points = points; }
        public void SetIsRoomAdmin(bool isRoomAdmin)
        {
            this.isRoomAdmin = isRoomAdmin;
        }
        public void SetRoom(RoomData room)
        {
            this.room = room;
        }
        public void ClearRoom()
        {
            this.room = new RoomData();
        }
    }
}
