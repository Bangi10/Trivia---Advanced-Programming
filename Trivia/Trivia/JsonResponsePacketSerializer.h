#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "RoomData.h"

namespace RESPONSES {
	enum class ERRORS { _ERROR = 50 };
	enum class LOGIN { SUCCESS = 100, USER_NOT_EXISTS = 101, USER_ALREADY_LOGINED = 102 };
	enum class SIGNUP { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
	enum class LOGOUT { SUCCESS = 120, USER_NOT_EXISTS = 103 };
	enum class ROOM { GET_PLAYER_IN_ROOM = 130 };
};

enum class RESPONSES { _ERROR = 255, LOGIN_Y = 101, LOGIN_N = 102, SIGNUP_Y = 111, SIGNUP_N = 112 };

struct ErrorResponse {
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
	static void addMsgLenToBuffer(Buffer& buffer, const std::string& msg);

};
