using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using Json = System.Text.Json;

namespace Trivia_Client.Code
{

    public class JsonSerialization
    {
        public static byte[] serializeRequest<T>(T request, RequestsCodes status) //even though status is in response, isn't accessible
        {
            List<byte> requestBuffer = new List<byte>();
            var jsonString = Json.JsonSerializer.Serialize(request);

            requestBuffer.Add((byte)status);
            requestBuffer.AddRange(getBigEndianBytesFromInt(jsonString.Length));
            requestBuffer.AddRange(Encoding.ASCII.GetBytes(jsonString));

            return requestBuffer.ToArray();
        }
        public static byte[] serializeRequestCode(RequestsCodes status) //even though status is in response, isn't accessible
        {
            List<byte> requestBuffer = new List<byte>();
            var jsonString = "{}";

            requestBuffer.Add((byte)status);
            requestBuffer.AddRange(getBigEndianBytesFromInt(jsonString.Length));
            requestBuffer.AddRange(Encoding.ASCII.GetBytes(jsonString));

            return requestBuffer.ToArray();
        }

        /// <summary>
        /// Function only gets json bytes without code and length
        /// Function may return default <typeparamref name="T"/> if not succeeded
        /// </summary>
        public static T? deserializeResponse<T>(byte[] jsonBuffer) 
        {
            string responseStr = Encoding.ASCII.GetString(jsonBuffer);
            try
            {
                T? responseObject = Json.JsonSerializer.Deserialize<T>(responseStr); //might fail and throw an exception 
                return responseObject;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
            return default(T);

        }
        public static byte[] getBigEndianBytesFromInt(int num)
        {
            byte[] bytes = BitConverter.GetBytes(num);

            if (BitConverter.IsLittleEndian)
                Array.Reverse(bytes);
            return bytes;
        }

    }
}
