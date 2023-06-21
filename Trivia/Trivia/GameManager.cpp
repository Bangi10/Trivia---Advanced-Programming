#include "GameManager.h"
#include <cmath>
#include <algorithm>

#define NUMBER_OF_QUESTIONS_IN_DB 10

GameManager::GameManager(std::shared_ptr<IDatabase>& db) :m_database(db)
{
}

Game& GameManager::createGame(Room& room)
{
	//get random questions from db
	int roomNumOfQuestions = room.getRoomNumOfQuestions();
	possibleExpandToQuestionsTable(roomNumOfQuestions);
	auto questions = this->m_database.lock()->getQuestions(roomNumOfQuestions);

	Game game(room);
	game.setQuestions(questions);
	this->m_games.push_back(game);
	return game;
}

bool GameManager::deleteGame(const unsigned int gameId)
{
	auto it = std::remove_if(m_games.begin(), m_games.end(), [gameId](const Game& game) {return game.getGameId() == gameId; });
	return it != m_games.end();
}

bool GameManager::doesGameExist(const unsigned int gameId)
{
	auto it = std::find_if(m_games.begin(), m_games.end(), [gameId](const Game& game) {return game.getGameId() == gameId; });
	return it != m_games.end();
}

bool GameManager::submitGameStatsToDB(const unsigned int gameId)
{
	auto gameIt = std::find_if(m_games.begin(), m_games.end(), [gameId](const Game& game) {return game.getGameId() == gameId; });
	if (gameIt == m_games.end())
		return false;
	auto players = gameIt->getPlayers();
	auto shared = this->m_database.lock();
	for (auto& player : players)
	{
		shared->updatePlayerStatistics(player.first.getUsername(), gameIt->calculateScore(player.first), player.second.averageAnswerTime,
									   player.second.correctAnswerCount, player.second.correctAnswerCount + player.second.wrongAnswerCount);
	}
	return true;	
}

void GameManager::possibleExpandToQuestionsTable(const int numOfQuestions)
{
	int runs = 0;
	if (numOfQuestions > NUMBER_OF_QUESTIONS_IN_DB)
	{
		runs = getRunsOfScript(numOfQuestions);
		for (int i = 0; i < runs; i++)
		{
			system("python db_add_questions.py");
		}
	}
}
int GameManager::getRunsOfScript(const int numOfQuestions)
{
	return (int)std::ceil((numOfQuestions - NUMBER_OF_QUESTIONS_IN_DB) / 10.0);
}
