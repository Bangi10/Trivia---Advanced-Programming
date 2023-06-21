#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <memory>

class GameManager
{
public:
	GameManager(std::vector<Game>& games, std::shared_ptr<IDatabase>& db);
	~GameManager();
	std::vector<Game> getGames()const;
	Game createGame(const Room& room);
	void deleteGame(const unsigned int gameID);

private:
	std::weak_ptr<IDatabase> m_database;
	std::vector<Game> m_games;
};