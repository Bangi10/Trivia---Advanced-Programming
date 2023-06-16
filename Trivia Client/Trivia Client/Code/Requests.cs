using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client.Code
{
    public enum RequestsCodes : byte
    {
        LOGIN = 200, SIGNUP = 201, LOGOUT = 202, CREATE_ROOM = 203,
        GET_ROOMS = 204, GET_PLAYERS_IN_ROOM = 205, JOIN_ROOM = 206,
        GET_STATISTICS = 207, GET_HIGH_SCORE = 208, CLOSE_ROOM = 209, START_GAME = 210,
        GET_ROOM_STATE = 211, LEAVE_ROOM = 212
    }

    public record struct LoginRequest(string username, string password);
    public record struct SignupRequest(string username, string password, string email);
    public record struct CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout);
    public record struct GetPlayersInRoomRequest(uint roomId);
    public record struct GetJoinRoomRequest(uint roomId);
}
