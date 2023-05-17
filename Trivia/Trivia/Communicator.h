#pragma once
#include <iostream>
#include <queue>
//#include <mutex>
//#include <condition_variable>
#include <WinSock2.h>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <map>
#include <string>
#include <thread>
#include <memory>

enum SERVER_DETAILS{SERVER_PORT = 8826, IFACE = 0};

typedef struct RequestInfo {
	unsigned char id;//byte 0-255
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};

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
	void handleNewClient(SOCKET sock);

	//std::queue<std::string> _messageHandler;

	//std::mutex _mtxReceivedMessages;
	//std::condition_variable _msgQueueCondition;

};