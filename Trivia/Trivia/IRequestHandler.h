#pragma once
#include <vector>

typedef struct RequestInfo {
	int id;
	time_t receivalTime;
	std::vector<unsigned char> Buffer;
};

class IRequestHandler
{
	virtual bool isRequestRelevant(const RequestInfo* requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo* requestInfo) const = 0;
	virtual ~IRequestHandler();

};