#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <list>
#include "Question.h"
#include <format>

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

	std::vector<Question> getQuestions(const int amount) const override;
	float getPlayerAverageAnswerTime(const std::string& username) const override;
	int getNumOfCorrectAnswers(const std::string& username) const override;
	int getNumOfTotalAnswers(const std::string& username) const override;
	int getNumOfPlayerGames(const std::string& username) const override;
	int getPlayerScore(const std::string& username) const override;
	std::string getHighScores() const override;
	bool checkIfQuestionsTableExists();
	void updatePlayerStatistics(const std::string& username, const int score, const float avgAnswerTime, const int numOfCorrectAnswers, const int numOfTotalAnswers) override;

private:
	sqlite3* _db;
};
