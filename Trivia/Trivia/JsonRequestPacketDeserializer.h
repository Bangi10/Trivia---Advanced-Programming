#pragma once
#include <vector>
#include <stdio.h>
#include <string>

typedef struct LoginRequest {
	std::string username;
	std::string password;
};

typedef struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> Buffer);
};