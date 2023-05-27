#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include <memory>

class Server
{
public:
<<<<<<< HEAD
	Server(std::shared_ptr<IDatabase> db);
=======
	Server(std::shared_ptr<IDatabase>& db);
>>>>>>> b868f45fac1eaef5f37d1b0e9f2bb14fca8e6a21
	~Server() = default;
	void run();

private:
	std::shared_ptr<IDatabase> m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
};