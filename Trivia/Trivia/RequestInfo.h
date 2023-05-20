#pragma once
#include <vector>
#include <ctime>

struct RequestInfo {
	unsigned char id;//byte 0-255
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};

