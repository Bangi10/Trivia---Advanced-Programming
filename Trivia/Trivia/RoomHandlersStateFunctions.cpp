#include "RoomHandlersStateFunctions.h"

GetRoomStateResponse RoomHandlersStateFunctions::createRoomStateResponse(const Room& room)
{
	GetRoomStateResponse response = { unsigned char(RESPONSES::ROOM::GOT_ROOM_STATE),
									 room.getRoomStatus() == unsigned char(ROOM_STATUS::IN_GAME),
									 room.getAllUsers(),
									 room.getRoomNumOfQuestions(),
									 room.getRoomTimePerQuestion() };
	return response;
}

GetRoomStateResponse RoomHandlersStateFunctions::createClosedRoomStateResponse()
{
	//Room is closed, no parameters except status
	GetRoomStateResponse response = { unsigned char(RESPONSES::ROOM::GOT_ROOM_STATE),
									 false,
									 std::vector<std::string>(),
									 0,
									 0 };
	return response;
}

RequestResult RoomHandlersStateFunctions::getRoomState(const RequestInfo& rInfo, const bool isAdmin, const int roomId, RequestHandlerFactory& m_handlerFactory, LoggedUser m_user)
{
	RequestResult result;
	auto& roomManager = m_handlerFactory.getRoomManager();
	Room room;
	GetRoomStateResponse response;
	try
	{
		room = roomManager.getRoom(roomId); //to get the most updated version of the room - might fail if room deleted recently
	}
	catch (const std::exception&)
	{
		//Room is closed, no parameters except status
		response = createClosedRoomStateResponse();
		result.response = JsonResponsePacketSerializer::serializeResponse(response);

		//Room is closed, return to menu
		result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
		return result;
	}

	unsigned int roomStatus = room.getRoomStatus();
	if (roomStatus == unsigned char(ROOM_STATUS::WAITING))
	{
		result.newHandler = isAdmin ? m_handlerFactory.createRoomAdminRequestHandler(m_user, room) :
									  m_handlerFactory.createRoomMemberRequestHandler(m_user, room);
	}
	else
	{
		result.newHandler = m_handlerFactory.createGameRequestHandler(m_user, room);
	}
	response = createRoomStateResponse(room);
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
