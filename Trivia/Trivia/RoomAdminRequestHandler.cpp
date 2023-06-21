#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RoomHandlersStateFunctions.h"

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
	auto& gameManager = this->m_handlerFactory.getGameManager();
	Game game = gameManager.createGame(m_room);
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user,game);
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo rInfo)
{
	return RoomHandlersStateFunctions::getRoomState(rInfo, true, m_room.getRoomID(), m_handlerFactory, m_user);	
}


