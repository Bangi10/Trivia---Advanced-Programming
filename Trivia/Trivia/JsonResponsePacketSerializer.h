#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "RoomData.h"
#include <vector>

namespace RESPONSES {
	enum class ERRORS :unsigned char { REQUEST_NOT_RELEVANT = 50 };
	enum class LOGOUT :unsigned char { SUCCESS = 90, USER_NOT_LOGINED = 91, NAME_NOT_EXISTS = 92 };
	enum class LOGIN :unsigned char { SUCCESS = 100, NAME_NOT_EXISTS = 101, PASSWORD_MISMATCH = 102, USER_ALREADY_LOGINED = 103 };
	enum class SIGNUP :unsigned char { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
	enum class ROOM :unsigned char {
		CREATED_ROOM = 120, GOT_ROOMS = 121, GOT_PLAYERS_IN_ROOM = 122,
		JOINED_ROOM = 123, GOT_HIGH_SCORE = 124, GOT_PERSONAL_STATS = 125, CLOSED_ROOM = 126,
		STARTED_GAME = 127, GOT_ROOM_STATE = 128, LEFT_ROOM = 129,
	};

};

enum class ROOM {
	STARTED = 130
};

struct ErrorResponse {
	unsigned int status;
	std::string message;
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	unsigned int status;
	std::vector<std::string> players;
};

struct getHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct getPersonalStatusResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};

struct CloseRoomResponse {
	unsigned int status;
};

struct StartGameResponse {
	unsigned int status;
};

struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector <std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse {
	unsigned int status;
};


using Buffer = std::vector<unsigned char>;

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);
	static Buffer serializeResponse(const LogoutResponse& response);
	static Buffer serializeResponse(const GetRoomsResponse& response);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& response);
	static Buffer serializeResponse(const JoinRoomResponse& response);
	static Buffer serializeResponse(const CreateRoomResponse& response);
	static Buffer serializeResponse(const getHighScoreResponse& response);
	static Buffer serializeResponse(const getPersonalStatusResponse& response);
	static Buffer serializeResponse(const CloseRoomResponse& response);
	static Buffer serializeResponse(const StartGameResponse& response);
	static Buffer serializeResponse(const GetRoomStateResponse& response);
	static Buffer serializeResponse(const LeaveRoomResponse& response);

	static void addMsgLenToBuffer(Buffer& buffer, const std::string& msg);

};