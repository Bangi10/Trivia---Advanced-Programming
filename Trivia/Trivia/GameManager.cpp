#include "GameManager.h"
#include <utility>

GameManager::GameManager(std::vector<Game>& games, std::shared_ptr<IDatabase>& db)
	:m_database(db),m_games(games)
{
}

GameManager::~GameManager()
{
	m_games.clear();
}

std::vector<Game> GameManager::getGames() const
{
	return m_games;
}

Game GameManager::createGame(const Room& room)
{
	std::list<Question> questionsList = m_database.lock()->getQuestions(5);
	std::vector<Question> questions;
	for (Question const& q : questionsList) {
		questions.push_back(q);
	}
	GameData gameData = {questions.front(),0,0,0};
	std::vector<std::string> users = room.getAllUsers();
	std::map<LoggedUser, GameData> players;
	for (std::string it : users)
	{
		LoggedUser user(it);
		std::pair<LoggedUser, GameData> pair(user,gameData);
		players.insert(pair);
	}
	m_games.emplace_back(questions, players, room.getRoomID());
	return Game(questions, players, room.getRoomID());
}

void GameManager::deleteGame(const unsigned int gameID)
{
	auto it = std::find(m_games.begin(),
		m_games.end(), gameID);
	m_games.erase(it);
}
