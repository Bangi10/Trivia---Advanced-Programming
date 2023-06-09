#pragma once

#include "RequestHandlerFactory.h"
#include "RoomManager.h"
class RequestHandlerFactory;
class RoomAdminRequestHandler : public IRequestHandler
{
public:
    RoomAdminRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
    ~RoomAdminRequestHandler() override = default;

    bool isRequestRelevant(const RequestInfo& requestInfo) const override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
    RequestResult closeRoom(RequestInfo rInfo);
    RequestResult startGame(RequestInfo rInfo);
    RequestResult getRoomState(RequestInfo rInfo);

    Room m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;
};