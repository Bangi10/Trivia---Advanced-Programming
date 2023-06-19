#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <list>
#include "Question.h"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase() final;
	bool open() override;
	void close() override;
	bool doesUserExists(const std::string& username) const override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) const override;
	void addNewUser(const std::string& username, const std::string& password, const std::string& email) override;

	std::list<Question> getQuestions(const int amount) const override;
	float getPlayerAverageAnswerTime(const std::string& username) const override;
	int getNumOfCorrectAnswers(const std::string& username) const override;
	int getNumOfTotalAnswers(const std::string& username) const override;
	int getNumOfPlayedGames(const std::string& username) const override;
	int getPlayerScore(const std::string& username) const override;
	std::string getHighScores() const override;
private:
	sqlite3* _db;
};
