#pragma once
#include "IRequestHandler.h"
#include <vector>
#include <memory>

class IRequestHandler;
using Buffer = std::vector<unsigned char>;


struct RequestResult {
	Buffer response;
	std::unique_ptr<IRequestHandler> newHandler;
};
