#include "SqliteDatabase.h"
#include <iostream>
#include "User.h"
#include <list>
#include <algorithm>
#include "Question.h"
#include "DBColumnNames.h"
#include <map>
#include "json.hpp"
using json = nlohmann::json;
const std::string fileName = "DB.sqlite";


int getFloatCallback(void* data, int argc, char** argv, char** azColName)
{
	auto dataPtr = (float*)data;
	*dataPtr = atof(argv[0]);
	return 0;
}

int getIntCallback(void* data, int argc, char** argv, char** azColName)
{
	auto dataPtr = (int*)data;
	*dataPtr = atoi(argv[0]);
	return 0;
}

int getUsersCallback(void* data, int argc, char** argv, char** azColName)
{
	auto users = (std::list<User>*)data;
	User user;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == USERNAME) {
			user.setUsername(argv[i]);
		}
		else if (std::string(azColName[i]) == PASSWORD) {
			user.setPassword(argv[i]);
		}
		else if (std::string(azColName[i]) == EMAIL) {
			user.setEmail(argv[i]);
		}
	}
	users->push_back(user);
	return 0;
}

int addHighScoreToMapCallBack(void* data, int argc, char** argv, char** azColName)
{
	auto scoreMap = (std::map<std::string, int>*)data;
	std::string username;
	int score;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == USERNAME) {
			username = argv[i];
		}
		else if (std::string(azColName[i]) == SCORE) {
			score = atoi(argv[i]);
		}
	}
	scoreMap->insert({ username, score });
	return 0;
}

int addQuestionToListCallback(void* data, int argc, char** argv, char** azColName)
{
	auto questionsList = (std::list<Question>*)data;
	std::string questionStr;
	std::vector<std::string> possibleAnswers;
	std::string correctAnswer;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == QUESTION) {
			questionStr = argv[i];
		}
		else if (std::string(azColName[i]) == ANSWER_INCORRECT1 || std::string(azColName[i]) == ANSWER_INCORRECT2 || std::string(azColName[i]) == ANSWER_INCORRECT3) {
			possibleAnswers.push_back(argv[i]);
		}
		else if (std::string(azColName[i]) == ANSWER_CORRECT) {
			correctAnswer = argv[i];
		}
	}
	Question question(questionStr, possibleAnswers, correctAnswer);
	questionsList->push_back(question);
	return 0;
}
bool SqliteDatabase::doesUserExists(const std::string& username) const
{
	//TODO add shared lock, shared mutex - multiple readers, one writer
	std::string msg = "SELECT * FROM USERS where USERS.USERNAME='" + username + "';";
	const char* sqlStatement = msg.c_str();
	char** errMessage = nullptr;
	std::list<User> usersList;
	int res = sqlite3_exec(this->_db, sqlStatement, getUsersCallback, &usersList, errMessage);
	if (res != SQLITE_OK) {
		return false;
	}

	auto it = std::find_if(
		usersList.begin(),
		usersList.end(),
		[username](const User& u) {return u.getUsername() == username; });
	return it != usersList.end();
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password) const
{
	//TODO add shared lock, shared mutex - multiple readers, one writer
	if (doesUserExists(username))
	{
		std::string msg = "SELECT* FROM USERS where USERS.USERNAME = '" + username + "' and USERS.PASSWORD = '" + password + "';";
		const char* sqlStatement = msg.c_str();
		char** errMessage = nullptr;
		std::list<User> usersList;
		int res = sqlite3_exec(this->_db, sqlStatement, getUsersCallback, &usersList, errMessage);
		if (res != SQLITE_OK) {
			return false;
		}
		for (auto it = usersList.begin(); it != usersList.end(); it++)
		{
			if (it->getUsername() == username && it->getPassword() == password)
				return true;
		}
		std::cout << "username and password mismatch" << std::endl;
		return false;
	}
	std::cout << "username doesnt exists" << std::endl;
	return false;
}

void SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	//TODO add unique lock, shared mutex - multiple readers, one writer
	if (doesUserExists(username))
	{
		std::cout << "add new user error:user already in DB" << std::endl;
	}
	else
	{
		std::string msg = "INSERT INTO USERS VALUES('" + username + "', '" + password + "', '" + email + "'); ";
		const char* sqlStatement = msg.c_str();
		sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, nullptr);
	}

}

std::list<Question> SqliteDatabase::getQuestions(const int amount) const
{
	std::string sqlStatement = "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + std::to_string(amount);
	std::list<Question> questionsList;
	sqlite3_exec(this->_db, sqlStatement.c_str(), addQuestionToListCallback, &questionsList, nullptr);
	return questionsList;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const std::string& username) const
{
	std::string sqlStatement = "SELECT " + AVG_ANSWER_TIME + " FROM STATISTICS WHERE USERNAME = " + username;
	float avgTime;
	sqlite3_exec(this->_db, sqlStatement.c_str(), getFloatCallback, &avgTime, nullptr);
	if (avgTime < 0)
		avgTime = 0;
	return avgTime;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username) const
{
	std::string sqlStatement = "SELECT " + NUM_OF_CORRECT_ANSWERS + " FROM STATISTICS WHERE USERNAME = " + username;
	int numOfCorrectAnswers;
	sqlite3_exec(this->_db, sqlStatement.c_str(), getIntCallback, &numOfCorrectAnswers, nullptr);
	if (numOfCorrectAnswers < 0)
		numOfCorrectAnswers = 0;
	return numOfCorrectAnswers;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& username) const
{
	std::string sqlStatement = "SELECT " + NUM_OF_TOTAL_ANSWERS + " FROM STATISTICS WHERE USERNAME = " + username;
	int numOfTotalAnswers;
	sqlite3_exec(this->_db, sqlStatement.c_str(), getIntCallback, &numOfTotalAnswers, nullptr);
	if (numOfTotalAnswers < 0)
		numOfTotalAnswers = 0;
	return numOfTotalAnswers;
}

int SqliteDatabase::getNumOfPlayedGames(const std::string& username) const
{
	std::string sqlStatement = "SELECT " + NUM_OF_PLAYER_GAMES + " FROM STATISTICS WHERE USERNAME = " + username;
	int numOfPlayedGames;
	sqlite3_exec(this->_db, sqlStatement.c_str(), getIntCallback, &numOfPlayedGames, nullptr);
	if (numOfPlayedGames < 0)
		numOfPlayedGames = 1;
	return numOfPlayedGames;
}

int SqliteDatabase::getPlayerScore(const std::string& username) const
{
	std::string sqlStatement = "SELECT " + SCORE + " FROM STATISTICS WHERE USERNAME = " + username;
	int score;
	sqlite3_exec(this->_db, sqlStatement.c_str(), getIntCallback, &score, nullptr);
	if (score < 0)
		score = 0;
	return score;
}

std::string SqliteDatabase::getHighScores() const
{
	std::map<std::string, int> highScoresMap;
	std::string sqlStatement = "SELECT USERNAME, SCORE FROM STATISTICS ORDER BY SCORE DESC LIMIT 5";
	sqlite3_exec(this->_db, sqlStatement.c_str(), addHighScoreToMapCallBack, &highScoresMap, nullptr);
	json highScoresJson = highScoresMap;
	return highScoresJson.dump();

}

SqliteDatabase::SqliteDatabase()
{
	if (open() == true)
	{
		std::cout << "Connected to database" << std::endl;
	}
	else
	{
		std::cout << "Failed to open DB" << std::endl;
	}
}

SqliteDatabase::~SqliteDatabase()
{
	close();
}

bool SqliteDatabase::open()
{
	std::string dbFileName = fileName;
	int res = sqlite3_open(dbFileName.c_str(), &_db);
	if (res != SQLITE_OK) {
		_db = nullptr;
		return false;
	}
	//creating new table USERS
	char** errMessage = nullptr;
	std::string sqlStatement = "CREATE TABLE USERS(USERNAME  TEXT NOT NULL, PASSWORD	TEXT NOT NULL, EMAIL  TEXT NOT NULL, PRIMARY KEY(USERNAME)); ";
	sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
	sqlStatement = "CREATE TABLE STATISTICS (USERNAME text NOT NULL , SCORE  int NOT NULL, AVG_ANSWER_TIME  float NOT NULL , NUM_OF_CORRECT_ANSWERS int NOT NULL , NUM_OF_TOTAL_ANSWERS   int NOT NULL , NUM_OF_PLAYER_GAMES    int NOT NULL ,PRIMARY KEY (USERNAME),FOREIGN KEY (USERNAME) REFERENCES USERS (USERNAME));";
	sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
	return true;
}


void SqliteDatabase::close()
{
	sqlite3_close(_db);
	_db = nullptr;
}
