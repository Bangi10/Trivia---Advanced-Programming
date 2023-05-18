#pragma once
#include <vector>
#include <string>

enum class REQUESTS :int { LOGIN = 100, SIGNUP = 110, BUFLEN = 1024 };


struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);
	static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);
};
