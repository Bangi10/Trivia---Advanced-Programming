#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

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

//NO DATA REQUESTS
struct HighScoreRequest {
	
};

struct LogoutRequest {

};
struct GetRoomRequest {

};

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);
	static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer);
	static JoinRoomRequest JoinRoomRequestdeserializeJoinRoomRequest(const std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer);
	//for HighScoreRequest, LogoutRequest, GetRoomRequest an empty struct will be created
};