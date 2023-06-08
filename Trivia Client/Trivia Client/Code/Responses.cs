using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client.Code
{
    namespace ResponseCodes
    {
        public enum ERRORS { REQUEST_NOT_RELEVANT = 50 };
        public enum LOGOUT { SUCCESS = 90, USER_NOT_EXISTS = 91 };
        public enum LOGIN { SUCCESS = 100, NAME_NOT_EXISTS = 101, PASSWORD_MISMATCH = 102, USER_ALREADY_LOGINED = 103 };
        public enum SIGNUP { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
        public enum ROOM
        {
            CREATED_ROOM = 130, GOT_ROOMS = 131, GOT_PLAYERS_IN_ROOM = 132,
            JOINED_ROOM = 133, GOT_HIGH_SCORE = 134, GOT_PERSONAL_STATS = 135
        };
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

