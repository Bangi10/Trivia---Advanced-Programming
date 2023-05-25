#include "LoginManager.h"
#include <iostream>

LoginManager::LoginManager(const std::shared_ptr<IDatabase> db)
{
	this->m_database = db;
}

LoginManager::~LoginManager()
{
	this->m_LoggedUsers.clear();
}

bool LoginManager::sigup(const std::string& username, const std::string& password, const std::string& email)
{
	auto sharedDb = this->m_database.lock();
	if (sharedDb->doesUserExists(username))
	{
		std::cout << "signup error:user already exists" << std::endl;
	}
	else
	{
		sharedDb->addNewUser(username, password, email);
		LoggedUser user(username);
		this->m_LoggedUsers.push_back(user);
	}
	return true;
}

bool LoginManager::login(const std::string& username, const std::string& password)
{
	auto sharedDb = this->m_database.lock();
	if (sharedDb->doesUserExists(username))
	{
		if (sharedDb->doesPasswordMatch(username, password))
		{
			LoggedUser user(username);
			this->m_LoggedUsers.push_back(user);
		}
		else
		{
			std::cout << "login error:password does not match user" << std::endl;
		}
	}
	else
	{
		std::cout << "login error:user does not exists" << std::endl;
	}
	return true;
}

bool LoginManager::logout(const std::string& username)
{
	auto sharedDb = this->m_database.lock();
	if (sharedDb->doesUserExists(username))
	{
		for (auto it = this->m_LoggedUsers.begin(); it != this->m_LoggedUsers.end(); it++)
		{
			if (it->getUsername() == username)
			{
				this->m_LoggedUsers.erase(it);
			}
		}
	}
	else
	{
		std::cout << "logout error:user does not exists" << std::endl;
	}
	return true;
}
