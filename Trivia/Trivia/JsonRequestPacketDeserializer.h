#pragma once
#include <vector>
#include <string>
#include <optional>

enum class REQUESTS:unsigned char { LOGIN = 200, SIGNUP = 201, LOGOUT = 202 };

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
	static std::optional<LoginRequest> deserializeLoginRequest(const std::vector<unsigned char>& buffer);
	static std::optional<SignupRequest> deserializeSignupRequest(const std::vector<unsigned char>& buffer);
};
