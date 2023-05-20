#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <thread>
#include <iostream>

using std::string;

using std::vector;
using std::cout;
using std::endl;
using std::unique_ptr;

Communicator::Communicator()
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
			this->m_clients[client_socket] = std::make_unique<LoginRequestHandler>(); //add to map

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

void Communicator::handleNewClient(SOCKET sock)
{
	while (this->m_clients.find(sock)->second != nullptr)
	{
		char recvbuf[int(REQUESTS::BUFLEN)];
		int byteCount = recv(sock, recvbuf, sizeof(recvbuf), 0);
		if (byteCount == 0)
			printf("Connection closed\n");
		else if (byteCount < 0)
			printf("recv failed: %d\n", WSAGetLastError());
		else
		{
			//ID
			unsigned char id = recvbuf[0];

			//convert char* to vector<unsigned char>
			Buffer clientMsg(byteCount);
			std::copy(recvbuf, recvbuf + byteCount, clientMsg.begin());

			if (id == int(REQUESTS::LOGIN))
			{
				LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(clientMsg);
				LoginResponse response;
				response.status = 1;
				Buffer loginResponse = JsonResponsePacketSerializer::serializeResponse(response);

			}
			else if (id == int(REQUESTS::SIGNUP))
			{
				SignupRequest signup = JsonRequestPacketDeserializer::deserializeSignupRequest(clientMsg);
				SignupResponse response;
				response.status = 1;
				Buffer signupResponse = JsonResponsePacketSerializer::serializeResponse(response);

			}
			else
			{
				ErrorResponse response;
				response.message = "ERROR";
				Buffer errorResponse = JsonResponsePacketSerializer::serializeResponse(response);
			}
		}
	}
	// cleanup
	closesocket(sock);
	WSACleanup();
}
