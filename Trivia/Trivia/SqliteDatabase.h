#pragma once
#include "IDatabase.h"
#include <map>
#include<vector>

class SqliteDatabase : public IDatabase
{
public:
	virtual bool open() const override;
	virtual bool close() const override;
	virtual bool doesUserExists(std::string& username) const override;
	virtual bool doesPasswordMatch(std::string& username, std::string& password) const override;
	virtual void addNewUser(std::string& username, std::string& password, std::string& email) const override;
	~SqliteDatabase() final = default;
private:
	//this std::map<std::string, std::pair<std::string, std::string>> _users doesnt let me do _users.insert() and i dont know why
	std::string* _username;
	std::string* _password;
	std::string* _email;
};