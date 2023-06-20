using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Trivia_Client.Code
{
    class Helper
    {
        public static bool isInEnum<T>(byte code)
        {
            return Enum.IsDefined(typeof(T), code);
        }
        public static bool Logout()
        {
            byte[] requestBuffer = JsonSerialization.serializeRequestCode(RequestsCodes.LOGOUT);
            ClientCommuinactor comm = ClientCommuinactor.Instance;
            comm.sendBytes(requestBuffer);

            var readTuple = comm.readBytes();
            byte[] jsonBuffer = readTuple.Item1;
            byte code = readTuple.Item2;

            if (isInEnum<ResponseCodes.ERRORS>(code))
            {
                ErrorResponse response = JsonSerialization.deserializeResponse<ErrorResponse>(jsonBuffer);
                MessageBox.Show(response.message);
                return false;
            }
            return true;
        }
    }
}
