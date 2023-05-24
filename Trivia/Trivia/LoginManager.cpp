#include "LoginManager.h"
#include <iostream>

LoginManager::LoginManager()
{
	this->m_database->open();
}

LoginManager::~LoginManager()
{
	delete[] this->m_database;
	this->m_LoggedUsers.clear();
}

void LoginManager::sigup(const std::string& username, const std::string& password, const std::string& email)
{
	if (this->m_database->doesUserExists(username))
	{
		std::cout << "signup error:user already exists" << std::endl;
	}
	else
	{
		this->m_database->addNewUser(username, password, email);
		LoggedUser user(username);
		this->m_LoggedUsers.push_back(user);
	}
}

void LoginManager::login(const std::string& username, const std::string& password)
{
	if (this->m_database->doesUserExists(username))
	{
		if (this->m_database->doesPasswordMatch(username, password))
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
}

void LoginManager::logout(const std::string& username)
{
	if (this->m_database->doesUserExists(username))
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
}
