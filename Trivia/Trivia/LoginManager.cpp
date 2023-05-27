#include "LoginManager.h"
#include <iostream>
#include "JsonResponsePacketSerializer.h"

LoginManager::LoginManager(std::shared_ptr<IDatabase>& db) :m_database(db)
{}


LoginManager::~LoginManager()
{
	this->m_LoggedUsers.clear();
}

int LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	auto sharedDb = this->m_database.lock();
	if (sharedDb->doesUserExists(username))
	{
		std::cout << "signup error:user already exists" << std::endl;
		return int(RESPONSES::SIGNUP::NAME_ALREADY_EXISTS);
	}
	sharedDb->addNewUser(username, password, email);
	LoggedUser user(username);
	this->m_LoggedUsers.push_back(user);
	return int(RESPONSES::SIGNUP::SUCCESS);
}

int LoginManager::login(const std::string& username, const std::string& password)
{
	auto sharedDb = this->m_database.lock();
	if (sharedDb->doesUserExists(username))
	{
		if (isLoggedIn(username))
		{
			std::cout << "login error:user already logged in" << std::endl;
			return int(RESPONSES::LOGIN::USER_ALREADY_LOGINED);
		}
		else if (!sharedDb->doesPasswordMatch(username, password))
		{
			std::cout << "login error: password doesn't match user" << std::endl;
			return int(RESPONSES::LOGIN::PASSWORD_MISMATCH);
		}
		LoggedUser user(username);
		this->m_LoggedUsers.push_back(user);
		return int(RESPONSES::LOGIN::SUCCESS);
	}
	std::cout << "login error:username does not exist" << std::endl;
	return int(RESPONSES::LOGIN::NAME_NOT_EXISTS);


}

int LoginManager::logout(const std::string& username)
{
	auto sharedDb = this->m_database.lock();
	for (auto it = this->m_LoggedUsers.begin(); it != this->m_LoggedUsers.end(); it++)
	{
		if (it->getUsername() == username)
		{
			this->m_LoggedUsers.erase(it);
			break;
		}
	}
	return int(RESPONSES::LOGOUT::SUCCESS);
}

bool LoginManager::isLoggedIn(const std::string& username)
{
	for (auto& it : this->m_LoggedUsers)
	{
		if (it.getUsername() == username)
			return true;
	}
	return false;
}
