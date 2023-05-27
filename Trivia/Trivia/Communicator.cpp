#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <thread>
#include <iostream>
#include <ctime>
#include <exception>
#include "Helper.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::unique_ptr;

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - create listening socket error");
}

Communicator::~Communicator()
{
	closesocket(m_serverSocket);
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	try
	{
		while (true)
		{
			// the main thread is only accepting clients 
			// and add then to the list of handlers
			cout << "accepting client..." << endl;

			SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
			if (client_socket == INVALID_SOCKET)
				throw std::exception(__FUNCTION__ " - create client socket error");

			cout << "Client accepted! " << endl;
			this->m_clients[client_socket] = this->m_handlerFactory.createLoginRequestHandler(); //add to map

			//handle client
			std::thread tr(&Communicator::handleNewClient, this, client_socket);
			tr.detach();
		}
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}

}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(SERVER_PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;

	// again stepping out to the global namespace
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	cout << "Binded..." << endl;

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	cout << "listening..." << endl;
}

void Communicator::handleNewClient(const SOCKET sock)
{
	unsigned char id = 0;
	int jsonMsgLen = 0;
	std::string jsonMsgStr;

	while (true)
	{
		try {
			id = Helper::getIntPartFromSocket(sock, int(LENGTH_OF::CODE));
			jsonMsgLen = Helper::getIntPartFromSocket(sock, int(LENGTH_OF::MSG_LENGTH));
			jsonMsgStr = Helper::getStringPartFromSocket(sock, jsonMsgLen);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			break;
		}
		Buffer jsonMsgBuffer(jsonMsgStr.begin(), jsonMsgStr.end());

		time_t receivalTime;
		time(&receivalTime);
		RequestInfo requestInfo{ id, receivalTime, jsonMsgBuffer };

		auto requestRes = this->m_clients[sock]->handleRequest(requestInfo);
		this->m_clients[sock] = std::move(requestRes.newHandler);

		Helper::sendData(sock, requestRes.response);
	}
	// cleanup
	closesocket(sock);
	WSACleanup();
}
