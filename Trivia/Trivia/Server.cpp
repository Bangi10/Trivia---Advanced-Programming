#include "Server.h"
#include <string>
#include <iostream>
#include <thread>

Server::Server(std::shared_ptr<IDatabase> db) : m_database(db),
m_handlerFactory(db),
m_communicator(this->m_handlerFactory)
{

}

void Server::run()
{
	std::thread tr_connector(&Communicator::startHandleRequests,
		std::ref(this->m_communicator));
	std::string input = "";

	do
	{
		std::cout << "Enter 'EXIT' when you want the program to end: ";
		std::cin >> input;
	} while (input != "EXIT");

	std::exit(0); // force all detached threads to finish and exit the program
}
