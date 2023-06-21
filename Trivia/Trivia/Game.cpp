#include "Game.h"

Game::Game(const std::vector<Question>& questions, const std::map<LoggedUser, GameData>& players, const unsigned int gameID)
	:m_questions(questions),m_players(players),m_gameID(gameID)
{
}

Game::~Game()
{
	m_questions.clear();
	m_players.clear();
}

unsigned int Game::getGameID() const
{
	return m_gameID;
}

std::vector<Question> Game::getQuestions() const
{
	return m_questions;
}

std::map<LoggedUser, GameData> Game::getPlayers() const
{
	return m_players;
}

Question Game::getQuestionForUser(const LoggedUser& user)const
{
	for (auto& it : m_players)
	{
		if (it.first.getUsername() == user.getUsername())
			return it.second.currentQuestion;
	}
	return Question("",{"",""},"");
}
