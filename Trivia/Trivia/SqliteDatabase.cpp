#include "SqliteDatabase.h"
#include <iostream>

bool SqliteDatabase::doesPasswordMatch(std::string& username, std::string& password) const
{
	if (doesUserExists(username))
	{
		for (int i = 0; i < _username->size(); i++)
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

void SqliteDatabase::addNewUser(std::string& username, std::string& password, std::string& email) const
{
	for (int i = 0; i < this->_username->size(); i++)
	{
		if (_username[i] == username && _password[i] == password && _email[i] == email)
		{
			std::cout << "this user already exists" << std::endl;
			return;
		}
	}
	_username->push_back(username);
	_password->push_back(password);
	_email->push_back(email);
	std::cout << "added user successfully" << std::endl;
}
