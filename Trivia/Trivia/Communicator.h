#pragma once
#include <iostream>
#include <queue>
//#include <mutex>
//#include <condition_variable>
#include <WinSock2.h>
#include "LoginRequestHandler.h"
#include <map>
#include <string>
#include <thread>
#include <memory>

enum SERVER_DETAILS{SERVER_PORT = 8826, IFACE = 0};
enum MESSAGE_DETAILS{MSG_LEN = 5, FLAGS = 0};
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