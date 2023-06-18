#include "RoomMamberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RoomMamberRequestHandler::RoomMamberRequestHandler(LoggedUser& user, Room& room, RequestHandlerFactory& handlerFactory) :
	m_handlerFactory(handlerFactory), m_room(room), m_user(user)
{
}

bool RoomMamberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (requestInfo.id >= unsigned char(REQUESTS::GET_ROOM_STATE) && requestInfo.id <= unsigned char(REQUESTS::LEAVE_ROOM))
		return true;
	return false;
}

RequestResult RoomMamberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult ret;
	REQUESTS id = REQUESTS(unsigned int(requestInfo.id));
	switch (id) {
	case REQUESTS::GET_ROOM_STATE:
		ret = this->leaveRoom(requestInfo);
		break;
	case REQUESTS::LEAVE_ROOM:
		ret = this->getRoomState(requestInfo);
		break;
	}
	return ret;
}

RequestResult RoomMamberRequestHandler::leaveRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	m_room.removeUser(m_user);
	LeaveRoomResponse response = { unsigned char(RESPONSES::ROOM::LEFT_ROOM) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult RoomMamberRequestHandler::getRoomState(const RequestInfo& requestInfo)
{
	RequestResult result;
	GetRoomStateResponse response = { unsigned char(RESPONSES::ROOM::GOT_ROOMS), m_room.getRoomStatus(),
									  m_room.getAllUsers(), m_room.getRoomNumOfQuestions(), m_room.getRoomTimePerQuestion() };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createRoomMamberRequestHandler(m_user, m_room);
	return result;
}