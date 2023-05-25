#pragma once
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"

class Room
{
public:
	Room(const RoomData& roomData);
	~Room();
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	//getters
	RoomData getMetaData()const;
	std::vector<std::string> getAllUsers()const;
	unsigned int getRoomID()const;
	std::string getRoomName()const;
	unsigned int getRoomMaxPlayers()const;
	unsigned int getRoomNumOfQuestions()const;
	unsigned int getRoomTimePerQuestion()const;
	bool isRoomActive()const;


private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};