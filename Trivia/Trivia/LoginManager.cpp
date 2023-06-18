#include "LoginManager.h"
#include <iostream>
#include "JsonResponsePacketSerializer.h"

//std::vector<LoggedUser> LoginManager::m_LoggedUsers = {};

LoginManager::LoginManager(std::shared_ptr<IDatabase>& db) :m_database(db)
{}


LoginManager::~LoginManager()
{
	m_LoggedUsers.clear();
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
		m_LoggedUsers.push_back(user);
		return int(RESPONSES::LOGIN::SUCCESS);
	}
	std::cout << "login error:username does not exist" << std::endl;
	return int(RESPONSES::LOGIN::NAME_NOT_EXISTS);


}

int LoginManager::logout(const std::string& username)
{
	auto sharedDb = this->m_database.lock();
	if (sharedDb->doesUserExists(username))
	{
		if (isLoggedIn(username))
		{
			for (auto it = m_LoggedUsers.begin(); it != m_LoggedUsers.end(); it++)
	{
		if (it->getUsername() == username)
		{
					m_LoggedUsers.erase(it);
			break;
		}
	}
	return int(RESPONSES::LOGOUT::SUCCESS);
}
		else
		{
			std::cout << "logout error:username does not logged in";
			return int(RESPONSES::LOGOUT::USER_NOT_LOGINED);
		}
	}
	else
	{
		std::cout << "logout error:username does not exist";
		return int(RESPONSES::LOGOUT::NAME_NOT_EXISTS);
	}
}

bool LoginManager::isLoggedIn(const std::string& username)
{
	for (auto& it : m_LoggedUsers)
	{
		if (it.getUsername() == username)
			return true;
	}
	return false;
}
