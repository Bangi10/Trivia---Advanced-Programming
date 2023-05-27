#include "Server.h"
#include <string>
#include <iostream>
#include <thread>

<<<<<<< HEAD
Server::Server(std::shared_ptr<IDatabase> db) : m_database(db),
=======
Server::Server(std::shared_ptr<IDatabase>& db) : m_database(db),
>>>>>>> b868f45fac1eaef5f37d1b0e9f2bb14fca8e6a21
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
