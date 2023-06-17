#pragma once
#include <WinSock2.h>
#include <map>
#include <memory>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

enum SERVER_DETAILS { SERVER_PORT = 8826, IFACE = 0 };

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequests();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, std::unique_ptr<IRequestHandler>> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	IRequestHandler* getClientHandler(const SOCKET sock);

	void bindAndListen();
	void handleNewClient(const SOCKET sock);
};