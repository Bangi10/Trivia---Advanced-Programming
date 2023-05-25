#pragma once
#include "IDatabase.h"
#include <vector>
#include "LoggedUser.h"
#include <memory>

class LoginManager
{
public:
	LoginManager();
	~LoginManager();
	int sigup(const std::string& username, const std::string& password, const std::string& email);
	int login(const std::string& username, const std::string& password);
	bool logout(const std::string& username);
	bool isLogedIn(const std::string& username);

private:
	std::weak_ptr<IDatabase> m_database;
	std::vector<LoggedUser> m_LoggedUsers;
};