#pragma once
#include "IRequestHandler.h"

typedef struct RequestResult {
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;

};

class LoginRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(const RequestInfo* requestInfo) const override;
	RequestResult handleRequest(const RequestInfo* requestInfo) const override;
};