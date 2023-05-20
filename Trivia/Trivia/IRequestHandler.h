#pragma once
#include <vector>
#include <ctime>

typedef std::vector<unsigned char> Buffer;

struct RequestInfo {
	unsigned char id;//byte 0-255
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};

struct RequestResult {
	Buffer response;
	std::unique_ptr<IRequestHandler> newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
	virtual ~IRequestHandler() = default;
};