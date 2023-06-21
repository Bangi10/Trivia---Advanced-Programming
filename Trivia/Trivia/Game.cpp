#include "Game.h"

Game::Game(Room& room) : m_room(room)
{
	this->m_gameId = room.getRoomID();
	initializePlayers(room);
	//questions will be initialized in game manager, no access here to db
	questionIndex = 0;
}

bool Game::getCurrentQuestionIfGameActive(Question& question, const std::string& username)
{
	if (questionIndex == m_questions.size())
		return false;
	question = m_questions.at(questionIndex);
	//if (username == this->m_players.)
	setCurrentQuestionForAll(m_questions.at(questionIndex));
	return true;

}

bool Game::submitAnswer(const std::string& answer, const std::string& username, const float userAnswerTime) const
{
	for (auto& player : this->m_players)
	{
		if (player.first.getUsername() == username)
		{
			return (player.second.currentQuestion.getCorrectAnswer() == answer);
		}
	}
	return false;
}

bool Game::removePlayer(const std::string& username)
{
	for (auto& player : this->m_players)
	{
		if (player.first.getUsername() == username)
		{
			//this->m_players.erase(player.first);
			return true;
		}
	}
	return false;
}

void Game::setQuestions(std::vector<Question> questions)
{
	this->m_questions = questions;
}

unsigned int Game::getGameId() const
{
	return this->m_gameId;
}

bool Game::operator==(const Game& other) const
{
	return this->m_gameId == other.m_gameId;
}

Game& Game::operator=(const Game& other)
{
	if (this != &other) {
		this->m_room = other.m_room;
		this->m_questions = other.m_questions;
		this->m_players = other.m_players;
		this->m_gameId = other.m_gameId;
		this->questionIndex = other.questionIndex;
	}
	return *this;
}

void Game::setCurrentQuestionForAll(Question question)
{
	for (auto& player : this->m_players)
	{
		player.second.currentQuestion = question;
	}
	questionIndex++;
}

void Game::initializePlayers(Room& room)
{
	auto players = room.getAllUsers();
	for(std::string& player: players)
	{
		m_players[LoggedUser(player)] = GameData{ Question(), 0, 0, 0 };
	}
}

