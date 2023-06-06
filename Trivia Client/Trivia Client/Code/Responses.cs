using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client.Code
{
    public class Responses
    {
        public enum CODES
        {
            
        }
        public record struct LoginResponse(byte status);
        public record struct SignupResponse(byte status);
        public record struct LogoutResponse(byte status);
        public record struct GetRoomsResponse(byte status, List<RoomData> rooms);
        public record struct RoomData(uint id, string name, uint maxPlayers, uint numOfQuestionsInGame, uint timePerQuestion, uint roomStatus);
        public record struct GetPlayersInRoomResponse(byte status, List<string> players);
        public record struct getHighScoreResponse(byte status, List<string> statistics);
        public record struct getPersonalStatusResponse(byte status, List<string> statistics);
        public record struct JoinRoomResponse(byte status);
        public record struct CreateRoomResponse(byte status);
    }
}
