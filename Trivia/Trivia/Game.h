#pragma once
#include "GameData.h"
#include <vector>
#include "LoggedUser.h"
#include "Question.h"
#include "User.h"
#include <map>

class Game
{
public:
	Game() = default;
	Game(const std::vector<Question>& questions, const std::map<LoggedUser, GameData>& players, const unsigned int gameID);
	~Game();
	//getters
	unsigned int getGameID()const;
	std::vector<Question> getQuestions()const;
	std::map<LoggedUser, GameData> getPlayers()const;
	Question getQuestionForUser(const LoggedUser& user)const;
	/*void submitAnswer();
	void removePlayer();*/

private:
	/*void submitGameStatsToDB(GameData gameData);*/
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameID;
};