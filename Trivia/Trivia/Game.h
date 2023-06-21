#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "GameData.h"
#include <vector>
#include <map>
#include "Room.h"

class Game
{
public:
	Game(Room& room);
	~Game() = default;

	bool getCurrentQuestionIfGameActive(Question& question, const std::string& username);
	bool submitAnswer(const std::string& answer, const std::string& username, const float userAnswerTime) const;
	bool removePlayer(const std::string& username);
	
	void setQuestions(std::vector<Question> questions);
	unsigned int getGameId() const;

	bool operator==(const Game& other) const;
	Game& operator=(const Game& other);

private:
	void initializePlayers(Room& room);
	void setCurrentQuestionForAll(Question question);

	Room& m_room;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
	int questionIndex;
};