#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include <memory>

class Server
{
public:
	Server(std::shared_ptr<IDatabase> db);
	~Server() = default;
	void run();

private:
	std::shared_ptr<IDatabase> m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
};