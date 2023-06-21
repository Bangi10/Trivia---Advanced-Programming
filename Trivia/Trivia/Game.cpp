#include "Game.h"

Game::Game(std::vector<Question>& questions, std::map<LoggedUser, GameData>& players, unsigned int gameID)
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

Question Game::getQuestionForUser(const LoggedUser& user) const
{
	return m_players.find(user)->second.currentQuestion;
}
