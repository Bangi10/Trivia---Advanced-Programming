#pragma once
#include "IDatabase.h"
#include <vector>
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager();
	~LoginManager();
	void sigup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_LoggedUsers;
};