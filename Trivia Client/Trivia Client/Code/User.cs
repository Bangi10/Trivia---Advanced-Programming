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
        private bool isRoomAdmin;
        private RoomData room;

        private User(string username)
        {
            this.username = username;
            this.isRoomAdmin = false;
            this.room = new RoomData();
        }
        public static User Instance(string username = "")
        {
            if (instance == null)
            {
                lock (syncRoot)
                {
                    if (instance == null)
                        instance = new User(username);
                }
            }

            return instance;
        }
        public string GetUsername()
        { 
            return username; 
        }
        public bool GetIsRoomAdmin()
        {
            return isRoomAdmin;
        }
        public RoomData GetRoom()
        {
            return room;
        }
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
