#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "PlayerResults.h"

GameRequestHandler::GameRequestHandler(Game& game, LoggedUser& user, GameManager& gameManager, RequestHandlerFactory& handlerFactory)
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
	REQUESTS id = static_cast<REQUESTS>(requestInfo.id);

	switch (id) {
	case REQUESTS::LEAVE_GAME:
		return this->leaveGame(requestInfo);
	case REQUESTS::GET_QUESTION:
		return this->getQuestion(requestInfo);
		/*case REQUESTS::SUBMIT_ANSWER:
			return this->submitAnswer(requestInfo);*/
	case REQUESTS::GET_GAME_RESULTS:
		return this->getGameResults(requestInfo);
	}
	return createErrorResponse();
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& requestInfo)
{
	RequestResult result;
	Question question;
	bool checkQuestion = m_game.getCurrentQuestionIfGameActive(question,m_user);
	GetQuestionResponse response = { unsigned char(RESPONSES::GAME::GET_QUESTION), question.getQuestion(),
		question.getPossibleAnswers()};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user, m_game);
	return result;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto request = JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(requestInfo.buffer);
	bool isCorrect = m_game.submitAnswer(request->answer, m_user, request->answerTime);
	SubmitAnswerResponse response = { unsigned char(RESPONSES::GAME::SUBMIT_ANSWER), isCorrect };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user, m_game);
	return result;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& requestInfo)
{
	RequestResult result;
	std::map<LoggedUser, GameData> players = m_game.getPlayers();
	std::vector<PlayerResults> results;
	for (auto& player : players)
	{
		PlayerResults playerResults = { player.first.getUsername(),player.second.correctAnswerCount,
										player.second.wrongAnswerCount,player.second.averageAnswerTime };
		results.push_back(playerResults);
	}
	GetGameResultsResponse response = { unsigned char(RESPONSES::GAME::GET_GAME_RESULTS), results };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user, m_game);
	return result;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	roomManager.getRoom(m_game.getGameId()).removeUser(m_user);
	LeaveGameRoomResponse response = { unsigned char(RESPONSES::GAME::LEFT_GAME) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult GameRequestHandler::createErrorResponse()
{
	ErrorResponse err = { unsigned char(RESPONSES::ERRORS::_ERROR),"AN ERROR OCCURED." };
	Buffer msg = JsonResponsePacketSerializer::serializeResponse(err);
	return RequestResult();
	return RequestResult{ msg, this->m_handlerFactory.createGameRequestHandler(m_user,m_game) };
}