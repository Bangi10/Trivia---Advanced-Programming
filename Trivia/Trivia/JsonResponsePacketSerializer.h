#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "RoomData.h"


namespace RESPONSES {
	enum class ERRORS :unsigned char { _ERROR = 50 };
	enum class LOGOUT :unsigned char { SUCCESS = 90 ,  USER_NOT_EXISTS = 91};
	enum class LOGIN :unsigned char { SUCCESS = 100, NAME_NOT_EXISTS = 101, PASSWORD_MISMATCH = 102, USER_ALREADY_LOGINED = 103 };
	enum class SIGNUP :unsigned char { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
	enum class ROOM :unsigned char { CREATED_ROOM = 120, GOT_ROOMS = 121, GOT_PLAYERS_IN_ROOM = 122,
								 	 JOINED_ROOM = 123, JOIN_ROOM_FULL = 130, GOT_HIGH_SCORE = 124, GOT_PERSONAL_STATS = 125, CLOSED_ROOM = 126,
									STARTED_GAME = 127, GOT_ROOM_STATE = 128, LEFT_ROOM = 129};

};

struct ErrorResponse {
	unsigned char status;
	std::string message;
};

struct LoginResponse {
	unsigned char status;
};

struct SignupResponse {
	unsigned char status;
};

struct LogoutResponse {
	unsigned char status;
};

struct GetRoomsResponse {
	unsigned char status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	unsigned char status;
	std::vector<std::string> players;
};

struct getHighScoreResponse {
	unsigned char status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned char status;
};

struct CreateRoomResponse {
	unsigned char status;
};

struct getPersonalStatusResponse {
	unsigned char status;
	std::string statistics;
};

struct CloseRoomResponse {
	unsigned char status;
};

struct StartGameResponse {
	unsigned char status;
};

struct GetRoomStateResponse {
	unsigned char status;
	bool hasGameBegun;
	std::vector <std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse {
	unsigned char status;
};

struct LeaveGameRoomResponse {
	unsigned char status;
};

struct GetQuestionResponse {
	unsigned char status;
	std::string question;
	std::map<unsigned int, std::string> answers;
};

struct SubmitAnswerResponse {
	unsigned char status;
	unsigned int correctAnswerID;
};

struct PlayerResults {
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

struct GetGameResultsResponse {
	unsigned char status;
	std::vector<PlayerResults> results;
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
