#include "SqliteDatabase.h"
#include <iostream>

bool SqliteDatabase::doesUserExists(const std::string& username) const
{
	for (int i = 0; i < _username.size(); i++)
	{
		if (_username[i] == username)
		{
			return true;
		}
	}
	return false;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password) const
{
	if (doesUserExists(username))
	{
		for (int i = 0; i < _username.size(); i++)
		{
			if (_username[i] == username && _password[i] == password)
			{
				return true;
			}
		}
		std::cout << "username and password mismatch" << std::endl;
		return false;
	}
	std::cout << "username doesnt exists" << std::endl;
	return false;
}

void SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email) 
{
	for (int i = 0; i < _username.size(); i++)
	{
		if (_username[i] == username && _password[i] == password && _email[i] == email)
		{
			std::cout << "this user already exists" << std::endl;
			return;
		}
	}
	addUsername(username);
	addPassword(password);
	addEmail(email);
	std::cout << "added user successfully" << std::endl;
}

void SqliteDatabase::addUsername(const std::string& username)
{
	this->_username.push_back(username);
}

void SqliteDatabase::addPassword(const std::string& password)
{
	_password.push_back(password);
}

void SqliteDatabase::addEmail(const std::string& email)
{
	_email.push_back(email);
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
	_username.clear();
	_password.clear();
	_email.clear();
	close();
}

bool SqliteDatabase::open()
{
	std::string dbFileName = "DB.sqlite";
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
