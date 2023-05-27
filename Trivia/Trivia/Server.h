#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include <memory>

class Server
{
public:
	Server(const std::shared_ptr<IDatabase> db);
	~Server() = default;
	void run();

private:
	Communicator m_communicator;
	std::shared_ptr<IDatabase> m_database;
	RequestHandlerFactory m_handlerFactory;
};