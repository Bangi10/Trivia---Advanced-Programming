#pragma once
#include "Communicator.h"

class Server
{
public:
	Server() = default;
	~Server() = default;
	void run();

private:
	Communicator m_communicator;

};
