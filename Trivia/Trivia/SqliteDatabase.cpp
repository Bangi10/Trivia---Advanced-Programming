#include "SqliteDatabase.h"
#include <iostream>

void SqliteDatabase::addNewUser(std::string& username, std::string& password, std::string& email) const
{
	for (int i = 0; i < this->_username->size(); i++)
	{
		if (_username[i] == username && _password[i] == password && _email[i] == email)
		{
			std::cout << "this user already exists" << std::endl;
		}
	}

}
