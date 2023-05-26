#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include <memory>

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(const std::shared_ptr<IDatabase> db);
	~RequestHandlerFactory() = default;

	std::unique_ptr<LoginRequestHandler> createLoginRequestHandler();
	std::unique_ptr<MenuRequestHandler> createMenuRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	std::weak_ptr<IDatabase> m_database;

};