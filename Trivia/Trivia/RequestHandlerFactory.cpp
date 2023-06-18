#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase>& db)
	:m_database(db), m_loginManager(db),m_statisticsManager(db)
{

}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_unique<LoginRequestHandler>(*this);
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
	return std::make_unique<MenuRequestHandler>(user, *this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}