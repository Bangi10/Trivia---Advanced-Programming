#pragma once

#include <vector>
#include <string>

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

using Buffer = std::vector<unsigned char>;



class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);
	static void addMsgLenToBuffer(Buffer& buffer, const std::string& msg);
};
