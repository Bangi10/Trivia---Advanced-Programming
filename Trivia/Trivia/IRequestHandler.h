#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"

using Buffer = std::vector<unsigned char>;

struct RequestResult;
class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
	virtual ~IRequestHandler() = default;
};