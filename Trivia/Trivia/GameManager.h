#pragma once
#include "IDatabase.h"
#include <vector>
#include <memory>
#include "Game.h"

class GameManager
{
public:
	GameManager(std::shared_ptr<IDatabase>& db);
	~GameManager() = default;

	Game& createGame(Room& room);
	void deleteGame(const unsigned int gameId);
	void submitGameStatsToDB(const unsigned int gameId);
private:
	std::weak_ptr<IDatabase> m_database;
	std::vector<Game> m_games;
};