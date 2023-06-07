#pragma once
#include <map>
#include "Room.h"
#include "LoggedUser.h"

class RoomManager
{
public:
	RoomManager() = default;
	~RoomManager();
	void createRoom(const LoggedUser& user, const RoomData& room);
	void deleteRoom(const unsigned int id);
	unsigned int getRoomState(const unsigned int id) ;
	std::vector<RoomData> getRooms()const;
	Room& getRoom(const unsigned int id);

private:
	std::map<unsigned int, Room> m_rooms;
};