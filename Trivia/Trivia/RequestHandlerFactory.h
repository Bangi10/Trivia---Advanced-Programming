#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include <memory>
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(std::shared_ptr<IDatabase>& db);
	~RequestHandlerFactory() = default;

	std::unique_ptr<IRequestHandler> createLoginRequestHandler();
	std::unique_ptr<IRequestHandler> createMenuRequestHandler();
	LoginManager& getLoginManager();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

private:
	std::weak_ptr<IDatabase> m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};