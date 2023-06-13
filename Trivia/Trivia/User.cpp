#include "User.h"

std::string User::getUsername() const
{
	return this->username;
}

std::string User::getPassword() const
{
	return this->password;
}

std::string User::getEmail() const
{
	return this->email;
}

void User::setUsername(const std::string& username)
{
	this->username = username;
}

void User::setPassword(const std::string& password)
{
	this->password = password;
}

void User::setEmail(const std::string& email)
{
	this->email = email;
}
