#include "RequestHandlerFactory.h"
using std::unique_ptr;
using std::make_unique;

RequestHandlerFactory::RequestHandlerFactory(const std::shared_ptr<IDatabase> db)
{
	this->m_database = db;
	this->m_loginManager = LoginManager(db);
}

unique_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return make_unique<LoginRequestHandler>(*this);
}

unique_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler()
{
	return make_unique<MenuRequestHandler>(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
