#pragma once
#include <vector>
#include <ctime>

typedef std::vector<unsigned char> Buffer;

typedef struct RequestInfo {
	unsigned char id;//byte 0-255
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};

typedef struct RequestResult {
	Buffer response;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo* requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo* requestInfo) = 0;
	virtual ~IRequestHandler() = default;

};