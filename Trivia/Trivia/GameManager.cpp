#include "GameManager.h"

GameManager::GameManager(std::shared_ptr<IDatabase>& db):m_database(db)
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

Game GameManager::getGame(const unsigned int gameID) const
{
	for (auto& game : m_games)
	{
		if (game.getGameID() == gameID)
			return game;
	}
	return Game();
}

Game GameManager::createGame(const Room& room)
{
	std::list<Question> questionsList = m_database.lock()->getQuestions(room.getRoomNumOfQuestions());
	std::vector<Question> questions;
	for (Question const& q : questionsList) {
		questions.push_back(q);
	}
	std::map<LoggedUser, GameData> players;
	for (auto& it : room.getAllUsers())
	{
		LoggedUser user(it);
		GameData gameData = { questions.front(),0,0,0 };
		players.insert({ user,gameData });
	} 
	unsigned int gameID = room.getRoomID();
	Game game(questions, players, gameID);
	m_games.push_back(game);

	return game;
}

void GameManager::deletGame(const unsigned int gameID)
{
	Game game = getGame(gameID);
	remove(m_games.begin(), m_games.end(), game);
}
