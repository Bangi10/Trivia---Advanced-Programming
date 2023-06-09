#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) :
	m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo rInfo)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo rInfo)
{
	return RequestResult();
}
