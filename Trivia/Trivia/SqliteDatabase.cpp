#include "SqliteDatabase.h"
#include <iostream>
#include "User.h"

//defines
const std::string fileName = "DB.sqlite";
const std::string USERNAME = "username";
const std::string PASSWORD = "password";
const std::string EMAIL = "EMAIL";

using users = std::list<User>;

users usersList;

int callback(void* data, int argc, char** argv, char** azColName)
{
	usersList.clear();
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
	usersList.push_back(user);
	return 0;
}

bool SqliteDatabase::doesUserExists(const std::string& username) const
{
	std::string msg = "SELECT * FROM USERS where USERS.USERNAME='" + username + "';";
	const char* sqlStatement = msg.c_str();
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement, callback, nullptr, errMessage);
	delete[] sqlStatement;
	if (res != SQLITE_OK) {
		return false;
	}
	for (auto it = usersList.begin(); it != usersList.end(); it++)
	{
		if (it->getUsername() == username)
			return true;
	}
	return false;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password) const
{
	if (doesUserExists(username))
	{
		std::string msg = "SELECT* FROM USERS where USERS.USERNAME = '" + username + "' and users.PASSWORD = " + password + ";";
		const char* sqlStatement = msg.c_str();
		char** errMessage = nullptr;
		int res = sqlite3_exec(this->_db, sqlStatement, callback, nullptr, errMessage);

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
	if (doesUserExists(username))
	{
		std::cout << "add new user error:user already in DB" << std::endl;
	}
	else
	{
		std::string msg = "INSERT INTO USERS VALUES('" + username + "', " + password + ", '" + email + "'); ";
		const char* sqlStatement = msg.c_str();
		sqlite3_exec(this->_db, sqlStatement, nullptr, nullptr, nullptr);

	}

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
	const char* sqlStatement = "CREATE TABLE USERS(USERNAME  TEXT NOT NULL, PASSWORD	TEXT NOT NULL, EMAIL  TEXT NOT NULL, PRIMARY KEY(USERNAME)); ";
	sqlite3_exec(_db, sqlStatement, nullptr, nullptr, errMessage);
	return true;
}

void SqliteDatabase::close()
{
	sqlite3_close(_db);
	_db = nullptr;
}

