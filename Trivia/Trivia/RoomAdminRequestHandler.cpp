#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) :
	m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo rInfo)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo rInfo)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo rInfo)
{
	return RequestResult();
}
