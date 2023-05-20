#pragma once
#include <string>

class IDatabase
{
public:
	virtual bool open() const  = 0;
	virtual bool close() const = 0;
	virtual bool doesUserExists(std::string& username) const = 0;
	virtual bool doesPasswordMatch(std::string& username, std::string& password) const = 0;
	virtual void addNewUser(std::string& username, std::string& password, std::string& email) const = 0;
	virtual ~IDatabase() = default;
};