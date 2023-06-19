#pragma once
#include <vector>
#include <string>
#include <optional>

enum class REQUESTS :unsigned char {
	LOGIN = 200, SIGNUP = 201, LOGOUT = 202, CREATE_ROOM = 203,
	GET_ROOMS = 204, GET_PLAYERS_IN_ROOM = 205, JOIN_ROOM = 206,
	GET_STATISTICS = 207, GET_HIGH_SCORE = 208, CLOSE_ROOM = 209, START_GAME = 210,
	GET_ROOM_STATE = 211, LEAVE_ROOM = 212
};


struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
};

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct GetPlayersInRoomRequest {
	unsigned int roomId;
};

struct JoinRoomRequest {
	unsigned int roomId;
};

class JsonRequestPacketDeserializer
{
public:
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer);
	//for HighScoreRequest, LogoutRequest, GetRoomRequest an empty struct will be created
	static std::optional<LoginRequest> deserializeLoginRequest(const std::vector<unsigned char>& buffer);
	static std::optional<SignupRequest> deserializeSignupRequest(const std::vector<unsigned char>& buffer);
};
