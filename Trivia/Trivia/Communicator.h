#pragma once


class Communicator
{
public:
	void startHandleRequests();
private:
	- m_serverSocket: SOCKET
	- m_clients : map<SOCKET, IRequestHandler*>
	+ 
	- bindAndListen()
	- handleNewClient(SOCKET)

};