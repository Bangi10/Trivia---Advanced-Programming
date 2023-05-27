#include <iostream>
#include <thread>
#include "Communicator.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

Communicator::Communicator(RequestHandlerFactory& handlerFactory):m_handlerFactory(handlerFactory)
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
			std::cout << "accepting client..." << std::endl;

			SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
			if (client_socket == INVALID_SOCKET)
				throw std::exception(__FUNCTION__ " - create client socket error");

			std::cout << "Client accepted! " << std::endl;
			this->m_clients[client_socket] = m_handlerFactory.createLoginRequestHandler(); //add to map

			//handle client
			std::thread tr(&Communicator::handleNewClient, this, client_socket);
			tr.detach();
		}
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << std::endl;
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
	std::cout << "Binded..." << std::endl;

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "listening..." << std::endl;
}

void Communicator::handleNewClient(const SOCKET sock)
{
	while (true)
	{
		if (this->m_clients.find(sock) == this->m_clients.end() || this->m_clients.find(sock)->second != nullptr)
		{
			break;
		}
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
				const char* msg = reinterpret_cast<char*>(loginResponse.data());
				send(sock, msg, strlen(msg), 0);
			}
			else if (id == int(REQUESTS::SIGNUP))
			{
				SignupRequest signup = JsonRequestPacketDeserializer::deserializeSignupRequest(clientMsg);
				SignupResponse response;
				response.status = 1;
				Buffer signupResponse = JsonResponsePacketSerializer::serializeResponse(response);
				const char* msg = reinterpret_cast<char*>(signupResponse.data());
				send(sock, msg, strlen(msg), 0);
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
