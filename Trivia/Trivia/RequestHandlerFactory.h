#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include <memory>



class RequestHandlerFactory
{
public:
	RequestHandlerFactory() = default;
	RequestHandlerFactory(std::shared_ptr<IDatabase>& db);
	~RequestHandlerFactory() = default;

	std::unique_ptr<IRequestHandler> createLoginRequestHandler();
	std::unique_ptr<IRequestHandler> createMenuRequestHandler();
	LoginManager& getLoginManager();

private:
	std::weak_ptr<IDatabase> m_database;
	LoginManager m_loginManager;

};
