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

	Question getQuestion() const;
	bool submitAnswer(const std::string& answer, LoggedUser& user);
	void removePlayer(const std::string& username);


private:
	Room& m_room;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
};