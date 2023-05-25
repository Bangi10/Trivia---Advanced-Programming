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
	unique_ptr<LoginRequestHandler> loginHandler = make_unique<LoginRequestHandler>(*this);
}

unique_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler()
{
	unique_ptr<MenuRequestHandler> loginHandler = make_unique<MenuRequestHandler>(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
