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
        private NetworkStream clientStream;

        private ClientCommuinactor()
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8826);
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();
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
            Int32 firstBytes = this.clientStream.Read(firstPart, 0, 1);

            //second to fifth bytes(size of the next text)
            byte[] secondPart = new byte[4];
            Int32 secondBytes = this.clientStream.Read(secondPart, 0, 4);

            //rest of the bytes
            Int32 sizeOfText = BitConverter.ToInt32(secondPart);
            byte[] thirdPart = new byte[sizeOfText];
            Int32 thirdBytes = this.clientStream.Read(thirdPart, 0, sizeOfText);


            return new Tuple<byte[], byte>(thirdPart, firstPart[0]);
        }
        public void sendBytes(byte[] bytesToSend)
        {
            this.clientStream.Write(bytesToSend, 0, bytesToSend.Length);
            this.clientStream.Flush();
        }
    }
}
