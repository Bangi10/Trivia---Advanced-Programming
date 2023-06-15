using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client.Code
{
    public class ResponseCodes
    {
        public enum ERRORS { _ERROR = 50 };
        public enum LOGOUT { SUCCESS = 90, USER_NOT_EXISTS = 91 };
        public enum LOGIN { SUCCESS = 100, NAME_NOT_EXISTS = 101, PASSWORD_MISMATCH = 102, USER_ALREADY_LOGINED = 103 };
        public enum SIGNUP { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
        public enum ROOM
        {
            CREATED_ROOM = 120, GOT_ROOMS = 121, GOT_PLAYERS_IN_ROOM = 122,
            JOINED_ROOM = 123, GOT_HIGH_SCORE = 124, GOT_PERSONAL_STATS = 125, CLOSED_ROOM = 126,
            STARTED_GAME = 127, GOT_ROOM_STATE = 128, LEFT_ROOM = 129
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

