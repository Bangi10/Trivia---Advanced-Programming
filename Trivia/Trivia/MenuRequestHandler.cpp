#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

//getting string that is separated by ":" and converting it to vector<string>
std::vector<std::string> stringToVectorSplit(std::string str, std::string delimiter)
{
	std::vector<std::string> v;
	if (!str.empty()) {
		int start = 0;
		do {
			// Find the index of occurrence
			int idx = str.find(delimiter, start);
			if (idx == std::string::npos) {
				break;
			}

			// If found add the substring till that
			// occurrence in the vector
			int length = idx - start;
			v.push_back(str.substr(start, length));
			start += (length + delimiter.size());
		} while (true);
		v.push_back(str.substr(start));
}
	return v;
}

MenuRequestHandler::MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& handlerFactory) : 
	m_handlerFactory(handlerFactory), m_user(user)
{

}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	if (requestInfo.id >= unsigned char(REQUESTS::CREATE_ROOM) && requestInfo.id <= unsigned char(REQUESTS::LOGOUT))
		return true;
	return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult ret;
	REQUESTS id = REQUESTS(unsigned int(requestInfo.id));
	switch (id) {
	case REQUESTS::CREATE_ROOM:
		ret = this->createRoom(requestInfo);
		break;
	case REQUESTS::GET_PLAYERS_IN_ROOM:
		ret = this->getPlayersInRoom(requestInfo);
		break;
	case REQUESTS::GET_ROOMS:
		ret = this->getRooms(requestInfo);
		break;
	case REQUESTS::GET_STATISTICS:
		ret = this->getPersonalStats(requestInfo);
		break;
	case REQUESTS::GET_HIGH_SCORE:
		ret = this->getHighScore(requestInfo);
		break;
	case REQUESTS::JOIN_ROOM:
		ret = this->joinRoom(requestInfo);
		break;
	case REQUESTS::LOGOUT:
		ret = this->logout(requestInfo);
		break;
	}
	return ret;
}

RequestResult MenuRequestHandler::logout(const RequestInfo& requestInfo)
{
	RequestResult result;
	LogoutResponse response = { unsigned char(RESPONSES::LOGOUT::SUCCESS) };
	this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	return result;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto roomManager = this->m_handlerFactory.getRoomManager();
	GetRoomsResponse response = { unsigned char(RESPONSES::ROOM::GOT_ROOMS), roomManager.getRooms()};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto roomManager = this->m_handlerFactory.getRoomManager();
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);
	unsigned int roomId = getPlayersInRoomRequest.roomId;
	auto players = roomManager.getRoom(roomId).getAllUsers();
	GetPlayersInRoomResponse response = { unsigned char(RESPONSES::ROOM::GOT_PLAYERS_IN_ROOM), players };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto statisticsManager = this->m_handlerFactory.getStatisticsManager();
	std::string userStatisticsString = statisticsManager.getUserStatistics(m_user.getUsername());
	std::vector<std::string> userStatistics = stringToVectorSplit(userStatisticsString, ":");
	getPersonalStatusResponse response = { unsigned char(RESPONSES::ROOM::GOT_PERSONAL_STATS), userStatistics };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto statisticsManager = this->m_handlerFactory.getStatisticsManager();
	std::string highScoresString = statisticsManager.getHighScores();
	std::vector<std::string> highScores = stringToVectorSplit(highScoresString, ":");
	getHighScoreResponse response = { unsigned char(RESPONSES::ROOM::GOT_HIGH_SCORE), highScores };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto roomManager = this->m_handlerFactory.getRoomManager();
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	unsigned int roomId = joinRoomRequest.roomId;
	roomManager.getRoom(roomId).addUser(m_user);
	JoinRoomResponse response = { unsigned char(RESPONSES::ROOM::JOINED_ROOM)};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;//needs to be new handler "RoomManagerRequestHandler" look in the state nachine uml
	return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto roomManager = this->m_handlerFactory.getRoomManager();
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
	auto rooms = roomManager.getRooms();
	unsigned int roomId = rooms.size() + 1;
	RoomData roomData = { roomId,createRoomRequest.roomName,createRoomRequest.maxUsers,
						 createRoomRequest.questionCount,createRoomRequest.answerTimeout,0 };
	roomManager.createRoom(m_user, roomData);
	CreateRoomResponse response = { unsigned char(RESPONSES::ROOM::CREATED_ROOM) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;//needs to be new handler "RoomManagerRequestHandler" look in the state nachine uml
	return result;
}


