#pragma once
#include <list>
#include <string>
#include "Question.h"

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual bool doesUserExists(const std::string& username) const = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) const = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual ~IDatabase() = default;

	virtual std::list<Question> getQuestions(const int amount) const = 0;
	virtual float getPlayerAverageAnswerTime(const std::string& username) const = 0;
	virtual int getNumOfCorrectAnswers(const std::string& username) const = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) const = 0;
	virtual int getNumOfPlayerGames(const std::string& username) const = 0;
	virtual int getPlayerScore(const std::string& username) const = 0;
	virtual std::string getHighScores() const = 0;
};