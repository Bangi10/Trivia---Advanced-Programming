#pragma once

#include "RequestHandlerFactory.h"
#include "RoomManager.h"
class RequestHandlerFactory;
class RoomMemberRequestHandler : public IRequestHandler
{
public:
    RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
    ~RoomMemberRequestHandler() override = default;

    bool isRequestRelevant(const RequestInfo& requestInfo) const override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
    RequestResult leaveRoom(RequestInfo rInfo);
    RequestResult getRoomState(RequestInfo rInfo);

    RequestResult createErrorResponse();

    Room m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
};