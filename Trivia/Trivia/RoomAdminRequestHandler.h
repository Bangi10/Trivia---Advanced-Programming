#pragma once
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(LoggedUser& user, Room& room, RequestHandlerFactory& handlerFactory);
	~RoomAdminRequestHandler()override = default;;
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	RequestHandlerFactory& m_handlerFactory;
	Room& m_room;
	LoggedUser m_user;
	RequestResult closeRoom(const RequestInfo& requestInfo);
	RequestResult startGame(const RequestInfo& requestInfo);
	RequestResult getRoomState(const RequestInfo& requestInfo);
};
