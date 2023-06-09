#pragma once
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"

enum class ROOM_STATUS {CLOSED = 0, WAITING = 1, IN_GAME = 2};

class Room
{
public:
	Room() = default;
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
	unsigned int getRoomStatus()const;
	void setRoomStatus(const unsigned int status);

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};