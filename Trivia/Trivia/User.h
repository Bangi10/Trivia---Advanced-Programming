#pragma once
#include <string>

class User {
public:
	User() = default;
	~User() = default;
	//getters
	std::string getUsername()const;
	std::string getPassword()const;
	std::string getEmail() const;
	//setters
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setEmail(const std::string& email);

private:
	std::string username;
	std::string password;
	std::string email;
};
