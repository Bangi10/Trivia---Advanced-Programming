#include "Communicator.h"

using std::string;
//using std::mutex;
//using std::unique_lock;
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
	//SEND
	string msg_to_client = "Hello";
	if (send(sock, msg_to_client.c_str(), msg_to_client.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
	cout << "Server: " << msg_to_client << endl;

	//GET
	char* msg_from_client = new char[MSG_LEN + 1];
	int res = recv(sock, msg_from_client, MSG_LEN, FLAGS);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sock);
		throw std::exception(s.c_str());
	}
	msg_from_client[MSG_LEN] = 0;
	std::string received(msg_from_client);
	delete[] msg_from_client;
	cout << "Client: " << msg_from_client << endl;
	
}
