#include "LoginManager.h"
#include <iostream>

LoginManager::LoginManager()
{
	this->m_database.lock()->open();
}

LoginManager::~LoginManager()
{
	this->m_LoggedUsers.clear();
}

bool LoginManager::sigup(const std::string& username, const std::string& password, const std::string& email)
{
	if (this->m_database.lock()->doesUserExists(username))
	{
		std::cout << "signup error:user already exists" << std::endl;
		return false;
	}
	else
	{
		this->m_database.lock()->addNewUser(username, password, email);
		LoggedUser user(username);
		this->m_LoggedUsers.push_back(user);
		return true;
	}
}

bool LoginManager::login(const std::string& username, const std::string& password)
{
	if (this->m_database.lock()->doesUserExists(username))
	{
		if (this->m_database.lock()->doesPasswordMatch(username, password))
		{
			LoggedUser user(username);
			this->m_LoggedUsers.push_back(user);
			return true;
		}
		else
		{
			std::cout << "login error:password does not match user" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "login error:user does not exists" << std::endl;
		return false;
	}
}

bool LoginManager::logout(const std::string& username)
{
	if (this->m_database.lock()->doesUserExists(username))
	{
		for (auto it = this->m_LoggedUsers.begin(); it != this->m_LoggedUsers.end(); it++)
		{
			if (it->getUsername() == username)
			{
				this->m_LoggedUsers.erase(it);
				return true;
			}
		}
	}
	else
	{
		std::cout << "logout error:user does not exists" << std::endl;
		return false;
	}
}
