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
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8826);
            client.Connect(serverEndPoint);
            ////sending message
            //NetworkStream clientStream = client.GetStream();
            //byte[] buffer = new ASCIIEncoding().GetBytes("Hello Server!");
            //clientStream.Write(buffer, 0, buffer.Length);
            //clientStream.Flush();
            ////getting message
            //buffer = new byte[4096];
            //int bytesRead = clientStream.Read(buffer, 0, 4096);
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
        public Tuple<byte[], byte> readBytes()
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


            return new Tuple<byte[], byte>(thirdPart, firstPart[0]);
        }
        public void sendBytes(byte[] bytesToSend)
        {
            m_socket.Send(bytesToSend, 0, bytesToSend.Length, SocketFlags.None);
        }
    }
}