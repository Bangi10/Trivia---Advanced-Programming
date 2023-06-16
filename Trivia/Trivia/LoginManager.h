#pragma once
#include "IDatabase.h"
#include <vector>
#include "LoggedUser.h"
#include <memory>

class LoginManager
{
public:
	LoginManager() = delete;
	LoginManager(std::shared_ptr<IDatabase>& db);
	~LoginManager();

	int signup(const std::string& username, const std::string& password, const std::string& email);
	int login(const std::string& username, const std::string& password);
	int logout(const std::string& username);

private:
	bool isLoggedIn(const std::string& username);

	std::weak_ptr<IDatabase> m_database;
	std::vector<LoggedUser> m_LoggedUsers;
};