#include "Room.h"

Room::Room(const RoomData& roomData) : m_metadata(roomData)
{
}

Room::~Room()
{
	this->m_users.clear();
}

void Room::addUser(const LoggedUser& user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
	for (auto it = this->m_users.begin();it !=this->m_users.end();it++)
	{
		if (it->getUsername() == user.getUsername())
		{
			this->m_users.erase(it);
		}
	}
}

RoomData Room::getMetaData() const
{
	return this->m_metadata;
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> allUsers;
	for (auto& it : this->m_users)
	{
		std::string username = it.getUsername();
		allUsers.push_back(username);
	}
	return allUsers;
}

unsigned int Room::getRoomID() const
{
	return this->m_metadata.id;
}

std::string Room::getRoomName() const
{
	return this->m_metadata.name;
}

unsigned int Room::getRoomMaxPlayers() const
{
	return this->m_metadata.maxPlayers;
}

unsigned int Room::getRoomNumOfQuestions() const
{
	return this->m_metadata.numOfQuestionsInGame;
}

unsigned int Room::getRoomTimePerQuestion() const
{
	return this->m_metadata.timePerQuestion;
}

int Room::getRoomStatus() const
{
	return this->m_metadata.roomStatus;
}
