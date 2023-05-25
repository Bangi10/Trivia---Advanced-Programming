#pragma once
#include <vector>
#include <string>
#include "json.hpp"

namespace RESPONSES {
	enum class ERRORS { _ERROR = 50 };
	enum class LOGIN { SUCCESS = 100, USER_NOT_EXISTS = 101, USER_ALREADY_LOGINED = 102 };
	enum class SIGNUP { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };
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

using Buffer = std::vector<unsigned char>;

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);
	static void addMsgLenToBuffer(Buffer& buffer, const std::string& msg);
};
