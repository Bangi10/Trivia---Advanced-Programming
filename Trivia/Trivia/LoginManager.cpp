#include "LoginManager.h"
#include <iostream>

enum class LOGOUT { SUCCESS = 90, USER_NOT_EXISTS = 91};
enum class LOGIN { SUCCESS = 100, USER_NOT_EXISTS = 101, USER_ALREADY_LOGINED = 102, PASSWORD_MISMATCH = 103};
enum class SIGNUP { SUCCESS = 110, NAME_ALREADY_EXISTS = 111 };

LoginManager::LoginManager()
{
	this->m_database.lock()->open();
}

LoginManager::~LoginManager()
{
	this->m_LoggedUsers.clear();
}

int LoginManager::sigup(const std::string& username, const std::string& password, const std::string& email)
{
	if (this->m_database.lock()->doesUserExists(username))
	{
		std::cout << "signup error:user already exists" << std::endl;
		return int(SIGNUP::NAME_ALREADY_EXISTS);
	}
	else
	{
		this->m_database.lock()->addNewUser(username, password, email);
		LoggedUser user(username);
		this->m_LoggedUsers.push_back(user);
	}
	return int(SIGNUP::SUCCESS);
}

int LoginManager::login(const std::string& username, const std::string& password)
{
	if (this->m_database.lock()->doesUserExists(username))
	{
		if (isLogedIn(username))
		{
			std::cout << "login error:user already logged in" << std::endl;
			return int(LOGIN::USER_ALREADY_LOGINED);
		}
		else if (this->m_database.lock()->doesPasswordMatch(username, password))
		{
			LoggedUser user(username);
			this->m_LoggedUsers.push_back(user);
			return int(LOGIN::SUCCESS);
		}
		else
		{
			std::cout << "login error:password does not match user" << std::endl;
			return int(LOGIN::PASSWORD_MISMATCH);
		}
	}
	else
	{
		std::cout << "login error:user does not exists" << std::endl;
		return int(LOGIN::USER_NOT_EXISTS);
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
				return int(LOGOUT::SUCCESS);
			}
		}
	}
	else
	{
		std::cout << "logout error:user does not exists" << std::endl;
		return int(LOGOUT::USER_NOT_EXISTS);
	}
}

bool LoginManager::isLogedIn(const std::string& username)
{
	for (auto& it : this->m_LoggedUsers)
	{
		if (it.getUsername() == username)
			return true;
	}
	return false;
}
