#pragma once
#include "IDatabase.h"
#include <map>
#include<vector>
#include "sqlite3.h"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase() final;
	bool open() override;
	void close() override;
	bool doesUserExists(const std::string& username) const override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) const override;
	void addNewUser(const std::string& username, const std::string& password, const std::string& email) override;
	void addUsername(const std::string& username);
	void addPassword(const std::string& password);
	void addEmail(const std::string& email);
private:
	//this std::map<std::string, std::pair<std::string, std::string>> _users doesnt let me do _users.insert() and i dont know why
	std::vector<std::string> _username;
	std::vector<std::string> _password;
	std::vector<std::string> _email;
	sqlite3* _db;
};