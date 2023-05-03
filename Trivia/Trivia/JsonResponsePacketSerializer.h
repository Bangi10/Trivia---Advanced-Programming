#pragma once
#include <iostream>
#include <vector>
#include <string>

typedef struct ErrorResponse {
	std::string message;
};

typedef struct LoginResponse {
	unsigned int status;
};

typedef struct SignupResponse {
	unsigned int status;
};

typedef std::vector<unsigned char> Buffer;

enum class RESPONSES { ERROR = 255, LOGIN_Y = 101, LOGIN_N = 102, SIGNUP_Y = 111, SIGNUP_N = 112 };
enum class REQUESTS { LOGIN = 100, SIGNUP = 110 };

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);
	static void addMsgLenToBuffer(Buffer& buffer, const std::string& msg);
};
