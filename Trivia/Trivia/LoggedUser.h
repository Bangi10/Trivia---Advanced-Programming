#pragma once
#include <string>

class LoggedUser{
public:
	LoggedUser() = default;
	LoggedUser(const std::string& username);
	~LoggedUser()=default;
	std::string getUsername() const;

private:
	std::string m_username;
};