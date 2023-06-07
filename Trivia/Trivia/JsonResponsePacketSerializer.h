#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "RoomData.h"


namespace RESPONSES {
	enum class ERRORS :unsigned char { REQUEST_NOT_RELEVANT = 50 };
	enum class LOGOUT :unsigned char { SUCCESS = 90 ,  USER_NOT_EXISTS = 91};
	enum class LOGIN :unsigned char { SUCCESS = 100, NAME_NOT_EXISTS = 101, PASSWORD_MISMATCH = 102, USER_ALREADY_LOGINED = 103 };
	enum class SIGNUP :unsigned char { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
	enum class ROOM :unsigned char{ GET_PLAYER_IN_ROOM = 130 };

};

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
