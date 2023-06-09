#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RoomHandlersStateFunctions.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) :
	m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (requestInfo.id < (unsigned char)REQUESTS::GET_ROOM_STATE || requestInfo.id >(unsigned char)REQUESTS::LEAVE_ROOM)
		return false;
	return true;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	REQUESTS requestId = static_cast<REQUESTS>(requestInfo.id);

	switch (requestId)
	{
	case REQUESTS::GET_ROOM_STATE:
		return getRoomState(requestInfo);
	case REQUESTS::LEAVE_ROOM:
		return leaveRoom(requestInfo);
	}
	return createErrorResponse();
}

RequestResult RoomMemberRequestHandler::createErrorResponse()
{
	ErrorResponse err = { unsigned char(RESPONSES::ERRORS::_ERROR),"AN ERROR OCCURED." };
	Buffer msg = JsonResponsePacketSerializer::serializeResponse(err);
	return RequestResult{ msg, this->m_handlerFactory.createRoomMemberRequestHandler(m_user, m_room) };
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo rInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	roomManager.getRoom(this->m_room.getRoomID()).removeUser(this->m_user);

	LeaveRoomResponse response = { unsigned char(RESPONSES::ROOM::LEFT_ROOM) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo rInfo)
{
	return RoomHandlersStateFunctions::getRoomState(rInfo, false, m_room.getRoomID(), m_handlerFactory, m_user);
}
