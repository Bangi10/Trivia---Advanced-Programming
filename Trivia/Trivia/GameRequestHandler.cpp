#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

GameRequestHandler::GameRequestHandler(Game& game, LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory)
	: m_game(game), m_user(user), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (requestInfo.id >= unsigned char(REQUESTS::LEAVE_GAME) && requestInfo.id <= unsigned char(REQUESTS::GET_GAME_RESULTS))
		return true;
	return false;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	REQUESTS requestId = static_cast<REQUESTS>(requestInfo.id);

	switch (requestId)
	{
	case REQUESTS::LEAVE_GAME:
		return leaveGame(requestInfo);
	case REQUESTS::GET_QUESTION:
		return getQuestion(requestInfo);
	case REQUESTS::SUBMIT_ANSWER:
		return submitAnswer(requestInfo);
	case REQUESTS::GET_GAME_RESULTS:
		return getGameResults(requestInfo);
	}
	return createErrorResponse();
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	roomManager.getRoom(m_game.getGameID()).removeUser(m_user);
	CloseRoomResponse response = { unsigned char(RESPONSES::GAME::LEFT_GAME)};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult GameRequestHandler::createErrorResponse()
{
	ErrorResponse err = { unsigned char(RESPONSES::ERRORS::_ERROR),"AN ERROR OCCURED." };
	Buffer msg = JsonResponsePacketSerializer::serializeResponse(err);
	return RequestResult{ msg, this->m_handlerFactory.createGameRequestHandler(m_user) };
}
