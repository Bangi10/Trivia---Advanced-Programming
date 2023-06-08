using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_Client.Code
{
    public enum RequestsCodes
    {
        LOGIN = 200, SIGNUP = 201, LOGOUT = 202, CREATE_ROOM = 120,
        GET_ROOMS = 121, GET_PLAYERS_IN_ROOM = 122, JOIN_ROOM = 123,
        GET_STATISTICS = 124
    }
    public record struct LoginRequest(string username, string password);
    public record struct SignupRequest(string username, string password, string email);
    public record struct CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout);
    public record struct GetPlayersInRoomRequest(uint roomId);
    public record struct GetJoinRoomRequest(uint roomId);
}
