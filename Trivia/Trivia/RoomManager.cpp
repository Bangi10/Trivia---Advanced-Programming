#include "RoomManager.h"
#include <iostream>
#include <utility>

RoomManager::~RoomManager()
{
	this->m_rooms.clear();
}

//i dont know what to do with user
void RoomManager::createRoom(const LoggedUser& user, const RoomData& room)
{
	std::pair<unsigned int, Room> idAndRoom(room.id, room);
	this->m_rooms.insert(idAndRoom);
}

void RoomManager::deleteRoom(const unsigned int id)
{
	for (auto& it : this->m_rooms)
	{
		if (it.first == id) {
			this->m_rooms.erase(id);
			return;
		}
	}
	std::cout << "delete Room error: room id:" << id << "does not exists" << std::endl;
}

unsigned int RoomManager::getRoomState(const unsigned int id)
{
	return this->getRoom(id).getRoomStatus();
}

std::vector<RoomData> RoomManager::getRooms() 
{
	std::vector<RoomData> allRooms;
	for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		RoomData roomData = it->second.getMetaData();
		allRooms.push_back(roomData);
	}
	return allRooms;
}

Room& RoomManager::getRoom(const unsigned int id)
{
	auto room = this->m_rooms.find(id);
	return room->second;
}
