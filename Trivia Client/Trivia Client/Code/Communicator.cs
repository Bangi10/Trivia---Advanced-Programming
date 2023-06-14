using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace Trivia_Client.Code
{
    public sealed class ClientCommuinactor 
    {
        public static volatile ClientCommuinactor instance;
        private static object syncRoot = new Object();

        //fields
        private Socket m_socket;
        

        private ClientCommuinactor()
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ipAddress = IPAddress.Parse("127.0.0.0");
            IPEndPoint remoteEndPoint = new IPEndPoint(ipAddress, 8826);
            socket.Connect(remoteEndPoint);
        }
        public static ClientCommuinactor Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (syncRoot)
                    {
                        if (instance == null)
                            instance = new ClientCommuinactor();
                    }
                }

                return instance;
            }
        }
        public byte[] readBytes()
        {
            //first byte
            byte[] firstPart = new byte[1];
            Int32 firstBytes = m_socket.Receive(firstPart, 1, 0);

            //second to fifth bytes(size of the next text)
            byte[] secondPart = new byte[4];
            Int32 secondBytes = m_socket.Receive(secondPart, 4, 0);

            //rest of the bytes
            
            Int32 sizeOfText = BitConverter.ToInt32(secondPart);
            byte[] thirdPart = new byte[sizeOfText];
            Int32 thirdBytes = m_socket.Receive(thirdPart, sizeOfText, 0);

            return thirdPart;
        }
        public void sendBytes(byte[] bytesToSend)
        {
            m_socket.Send(bytesToSend, 0, bytesToSend.Length, SocketFlags.None);
        }
    }
}
