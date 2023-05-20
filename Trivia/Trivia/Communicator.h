#pragma once
#include <WinSock2.h>
#include <map>
#include <memory>
#include "IRequestHandler.h"

enum SERVER_DETAILS { SERVER_PORT = 8826, IFACE = 0 };

class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequests();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, std::unique_ptr<IRequestHandler>> m_clients;

	void bindAndListen();
	void handleNewClient(const SOCKET sock);
};
