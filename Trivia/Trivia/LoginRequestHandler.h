#pragma once
#include "IRequestHandler.h"

enum class REQUESTS { LOGIN = 100, SIGNUP = 110 };
enum class RESPONSES { ERROR = 255, LOGIN_Y = 101, LOGIN_N = 102, SIGNUP_Y = 111, SIGNUP_N = 112 };

class LoginRequestHandler : public IRequestHandler
{
public:
	~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};