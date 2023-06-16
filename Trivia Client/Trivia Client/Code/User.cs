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


        private User(string username)
        {
            this.username = username;
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
        public string getUsername()
        { 
            return username; 
        }
    }
}