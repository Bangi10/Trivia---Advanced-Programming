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
	bool deleteGame(const unsigned int gameId);
	bool doesGameExist(const unsigned int gameId);
	void submitGameStatsToDB(const unsigned int gameId);
private:
	static void possibleExpandToQuestionsTable(const int numOfQuestions);
	static int getRunsOfScript(const int numOfQuestions);

	std::weak_ptr<IDatabase> m_database;
	std::vector<Game> m_games;
};