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

namespace Trivia_Client
{
    public class ClientCommuinactor 
    {
        private static readonly Socket m_socket;

        private static ClientCommuinactor()
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ipAddress = IPAddress.Parse("127.0.0.0");
            IPEndPoint remoteEndPoint = new IPEndPoint(ipAddress, 8826);
            socket.Connect(remoteEndPoint);
        }

        public static byte[] readBytes()
        {
            //first byte
            byte[] firstPart = new byte[1];
            Int32 firstBytes = m_socket.Receive(firstPart, 1, 0);
            //second to fifth bytes(size of the next text)
            byte[] secondPart = new byte[4];
            Int32 secondBytes = m_socket.Receive(secondPart, 4, 0);
            //rest of the bytes
            Int32 sizeOfText = secondBytes;
            byte[] thirdPart = new byte[sizeOfText];
            Int32 thirdBytes = m_socket.Receive(thirdPart, sizeOfText, 0);
            //all bytes together
            byte[] allParts = new byte[firstBytes + secondBytes + thirdBytes];
            allParts[0] = firstPart[0];
            int i = 1;
            for (int j = 0; j < secondPart.Length; j++, i++)
            {
                allParts[i] = secondPart[j];
            }
            for (int j = 0; j < thirdPart.Length; j++, i++)
            {
                allParts[i] = thirdPart[j];
            }
            return allParts;
        }
        public static void sendBytes(byte[] bytesToSend)
        {
            m_socket.Send(bytesToSend, 0, bytesToSend.Length, SocketFlags.None);
        }
    }
}
