#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) :
	m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (requestInfo.id < (unsigned char)REQUESTS::CLOSE_ROOM || requestInfo.id >(unsigned char)REQUESTS::GET_ROOM_STATE)
		return false;
	return true;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	REQUESTS requestId = static_cast<REQUESTS>(requestInfo.id);

	switch (requestId)
	{
	case REQUESTS::CLOSE_ROOM:
		return closeRoom(requestInfo);
	case REQUESTS::START_GAME:
		return startGame(requestInfo);
	case REQUESTS::GET_ROOM_STATE:
		return getRoomState(requestInfo);
	}
	return createErrorResponse();
}

RequestResult RoomAdminRequestHandler::createErrorResponse()
{
	ErrorResponse err = { unsigned char(RESPONSES::ERRORS::_ERROR),"AN ERROR OCCURED." };
	Buffer msg = JsonResponsePacketSerializer::serializeResponse(err);
	return RequestResult{ msg, this->m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room)};
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo rInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	roomManager.deleteRoom(this->m_room.getRoomID());
	
	CloseRoomResponse response = { unsigned char(RESPONSES::ROOM::CLOSED_ROOM)};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo rInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	roomManager.getRoom(m_room.getRoomID()).setRoomStatus((unsigned int)ROOM_STATUS::IN_GAME);

	StartGameResponse response = { unsigned char(RESPONSES::ROOM::STARTED_GAME) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user, m_room);
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo rInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	Room room;
	GetRoomStateResponse response;
	try
	{
		room = roomManager.getRoom(m_room.getRoomID()); //to get the most updated version of the room - might fail if room deleted recently
	}
	catch (const std::exception&)
	{
		//Room is closed, no parameters except status
		response = createClosedRoomStateResponse();
		result.response = JsonResponsePacketSerializer::serializeResponse(response);

		//Room is closed, return to menu
		result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
		return result;
	}

	unsigned int roomStatus = room.getRoomStatus();
	if (roomStatus == unsigned char(ROOM_STATUS::WAITING))
		result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room);
	else
		result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user, m_room);

	response = createRoomStateResponse(room);
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
	
}

GetRoomStateResponse RoomAdminRequestHandler::createRoomStateResponse(const Room& room)
{
	GetRoomStateResponse response = {room.getRoomStatus() ,
									 room.getRoomStatus() == unsigned char(ROOM_STATUS::IN_GAME),
									 room.getAllUsers(),
									 room.getRoomNumOfQuestions(),
									 room.getRoomTimePerQuestion() };
	return response;
}

GetRoomStateResponse RoomAdminRequestHandler::createClosedRoomStateResponse()
{
	//Room is closed, no parameters except status
	GetRoomStateResponse response = { unsigned char(RESPONSES::ROOM::CLOSED_ROOM),
									 false,
									 std::vector<std::string>(),
									 0,
									 0 };
	return response;
}
