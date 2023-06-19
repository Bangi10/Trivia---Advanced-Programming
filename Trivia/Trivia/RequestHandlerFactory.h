#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include <memory>



class RequestHandlerFactory
{
public:
	RequestHandlerFactory(std::shared_ptr<IDatabase>& db);
	~RequestHandlerFactory() = default;

	std::unique_ptr<IRequestHandler> createLoginRequestHandler();
	std::unique_ptr<IRequestHandler> createMenuRequestHandler(LoggedUser& user);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
	std::unique_ptr<IRequestHandler> createRoomAdminRequestHandler(LoggedUser& user, Room& room);
	std::unique_ptr<IRequestHandler> createRoomMamberRequestHandler(LoggedUser& user, Room& room);


private:
	std::weak_ptr<IDatabase> m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;

};