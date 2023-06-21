#pragma once
#include <map>
#include "Room.h"
#include "LoggedUser.h"
#include <memory>
#include "SqliteDatabase.h"
#include "Game.h"

class GameManager
{
public:
	explicit GameManager(std::shared_ptr<IDatabase>& db);
	~GameManager();
	std::vector<Game> getGames()const;
	Game getGame(const unsigned int gameID)const;
	Game createGame(const Room& room);
	void deletGame(const unsigned int gameID);

private:
	std::weak_ptr<IDatabase> m_database;
	std::vector<Game> m_games;
};