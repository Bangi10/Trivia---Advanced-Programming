#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"


RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase>& db)
	:m_database(db), m_loginManager(db),m_statisticsManager(db)//,m_gameManager(db)
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

//GameManager& RequestHandlerFactory::getGameManager()
//{
//	return m_gameManager;
//}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room& room)
{
	return std::make_unique<RoomAdminRequestHandler>(room, user, this->m_roomManager, *this);
}

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room& room)
{
	return std::make_unique<RoomMemberRequestHandler>(room, user, this->m_roomManager, *this);
}

//std::unique_ptr<IRequestHandler> RequestHandlerFactory::createGameRequestHandler(LoggedUser& user, Game& game)
//{
//	return std::make_unique<GameRequestHandler>(game, user, this->m_gameManager, *this);
//}
