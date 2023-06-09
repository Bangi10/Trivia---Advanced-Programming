#pragma once
#include "Room.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestInfo.h"
#include "RequestResult.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RoomHandlersStateFunctions
{
public:
	static RequestResult getRoomState(const RequestInfo& rInfo, const bool isAdmin, const int roomId, RequestHandlerFactory& m_handlerFactory, LoggedUser m_user);
private:
	static GetRoomStateResponse createRoomStateResponse(const Room& room);
	static GetRoomStateResponse createClosedRoomStateResponse();

};