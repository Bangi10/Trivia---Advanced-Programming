#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser& user, Room& room, RequestHandlerFactory& handlerFactory) :
	m_handlerFactory(handlerFactory), m_room(room), m_user(user)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (requestInfo.id >= unsigned char(REQUESTS::CLOSE_ROOM) && requestInfo.id <= unsigned char(REQUESTS::GET_ROOM_STATE))
		return true;
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult ret;
	REQUESTS id = REQUESTS(unsigned int(requestInfo.id));
	switch (id) {
	case REQUESTS::CLOSE_ROOM:
		ret = this->closeRoom(requestInfo);
		break;
	case REQUESTS::START_GAME:
		ret = this->startGame(requestInfo);
		break;
	case REQUESTS::GET_ROOM_STATE:
		ret = this->getRoomState(requestInfo);
		break;
	}
	return ret;
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	m_handlerFactory.getRoomManager().deleteRoom(m_room.getRoomID());
	CloseRoomResponse response = { unsigned char(RESPONSES::ROOM::CLOSED_ROOM) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& requestInfo)
{
	RequestResult result;
	RoomData roomData = m_room.getMetaData();//mabey it wouldnt work because this isnt a ref 
	roomData.roomStatus = unsigned int(unsigned char(ROOM::STARTED) - '0');
	StartGameResponse response = { unsigned char(RESPONSES::ROOM::STARTED_GAME) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	//commiting because function 'createGameRequestHandler' doesnt exists yet
	//result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user);
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& requestInfo)
{
	RequestResult result;
	GetRoomStateResponse response = { unsigned char(RESPONSES::ROOM::GOT_ROOMS), m_room.getRoomStatus(),
									  m_room.getAllUsers(), m_room.getRoomNumOfQuestions(), m_room.getRoomTimePerQuestion() };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room);
	return result;
}