#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& handlerFactory);
	~MenuRequestHandler() override = default;

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	LoggedUser m_user;
	RequestResult logout(const RequestInfo& requestInfo);
	RequestResult getRooms(const RequestInfo& requestInfo);
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo);
	RequestResult getPersonalStats(const RequestInfo& requestInfo);
	RequestResult getHighScore(const RequestInfo& requestInfo);
	RequestResult joinRoom(const RequestInfo& requestInfo);
	RequestResult createRoom(const RequestInfo& requestInfo);
};
