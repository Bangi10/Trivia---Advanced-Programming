#include "Game.h"

Game::Game(Room& room) : m_room(room)
{
	this->m_gameId = room.getRoomID();
	initializePlayers(room);
	questionIndex = 0;
	//questions will be initialized in game manager, no access here to db
}

bool Game::getCurrentQuestionIfGameActive(Question& question, const LoggedUser& user)
{
	if (questionIndex == m_questions.size())
		return false;
	question = m_questions.at(questionIndex);
	if (user == this->m_players.begin()->first)
	{
		//do this only once each round
		setCurrentQuestionForAll(m_questions.at(questionIndex));
	}
	return true;

}

bool Game::submitAnswer(const std::string& answer, const LoggedUser& user, const float userAnswerTime)
{
	auto it = m_players.find(user);
	if (it == m_players.end())
		return false;
	float oldAvgTime = it->second.averageAnswerTime;
	it->second.averageAnswerTime = (oldAvgTime * (questionIndex) + userAnswerTime) / (questionIndex + 1);
	if (answer == it->second.currentQuestion.getCorrectAnswer())
	{
		it->second.correctAnswerCount++;
		return true;
	}
	it->second.wrongAnswerCount++;
	return false;
}	

bool Game::removePlayer(const LoggedUser& user)
{
	auto it = m_players.find(user);
	if (it == m_players.end())
		return false;
	m_players.erase(it);
	return true;
}

void Game::setQuestions(std::vector<Question> questions)
{
	this->m_questions = questions;
}

unsigned int Game::getGameId() const
{
	return this->m_gameId;
}

std::map<LoggedUser, GameData> Game::getPlayers() const
{
	return this->m_players;
}

float Game::calculateScore(const LoggedUser& user)
{
	auto it = m_players.find(user);
	if (it == m_players.end())
		return 0.0;
	return (it->second.correctAnswerCount * 10) / it->second.averageAnswerTime;
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

