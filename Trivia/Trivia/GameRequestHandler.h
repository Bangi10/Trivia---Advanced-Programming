#pragma once
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class GameRequestHandler : public IRequestHandler
{
public:
    GameRequestHandler(Game& game, LoggedUser& user, GameManager& gameManager, RequestHandlerFactory& handlerFactory);
    ~GameRequestHandler() override = default;

    bool isRequestRelevant(const RequestInfo& requestInfo) const override;
    RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
    RequestResult getQuestion(const RequestInfo& requestInfo);
    RequestResult submitAnswer(const RequestInfo& requestInfo);
    RequestResult getGameResults(const RequestInfo& requestInfo);
    RequestResult leaveGame(const RequestInfo& requestInfo);

    RequestResult createErrorResponse();

    Game& m_game;
    LoggedUser m_user;
    GameManager& m_gameManager;
    RequestHandlerFactory& m_handlerFactory;
};