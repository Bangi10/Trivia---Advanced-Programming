#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RoomManager.h"
#include "json.hpp"
using json = nlohmann::json;

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
	if (requestInfo.id < unsigned char(REQUESTS::LOGOUT) && requestInfo.id <= unsigned char(REQUESTS::GET_HIGH_SCORE))
		return true;
	return false;
}


RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	REQUESTS id = static_cast<REQUESTS>(requestInfo.id);

	switch (id) {
		case REQUESTS::CREATE_ROOM:
			return this->createRoom(requestInfo);
		case REQUESTS::GET_PLAYERS_IN_ROOM:
			return this->getPlayersInRoom(requestInfo);
		case REQUESTS::GET_ROOMS:
			return this->getRooms(requestInfo);
		case REQUESTS::GET_STATISTICS:
			return this->getPersonalStats(requestInfo);
		case REQUESTS::GET_HIGH_SCORE:
			return this->getHighScore(requestInfo);
		case REQUESTS::JOIN_ROOM:
			return this->joinRoom(requestInfo);
		case REQUESTS::LOGOUT:
			return this->logout(requestInfo);
	}
	return createErrorResponse();
}

RequestResult MenuRequestHandler::createErrorResponse()
{
	ErrorResponse err = { unsigned char(RESPONSES::ERRORS::_ERROR),"AN ERROR OCCURED." };
	Buffer msg = JsonResponsePacketSerializer::serializeResponse(err);
	return RequestResult{ msg, this->m_handlerFactory.createMenuRequestHandler(this->m_user) };
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
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	GetRoomsResponse response = { unsigned char(RESPONSES::ROOM::GOT_ROOMS), roomManager.getRooms()};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	auto getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);
	if (!getPlayersInRoomRequest)
		return createErrorResponse();
	unsigned int roomId = getPlayersInRoomRequest.value().roomId;
	std::vector<std::string> players = {};
	try 
	{
		players = roomManager.getRoom(roomId).getAllUsers();
	}
	catch (std::exception& e)
	{
		//room deleted, no players in it
	}
	GetPlayersInRoomResponse response = { unsigned char(RESPONSES::ROOM::GOT_PLAYERS_IN_ROOM), players };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto& statisticsManager = this->m_handlerFactory.getStatisticsManager();
	std::string userStatisticsString = statisticsManager.getUserStatistics(m_user.getUsername());
	getPersonalStatusResponse response = { unsigned char(RESPONSES::ROOM::GOT_PERSONAL_STATS), userStatisticsString };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto& statisticsManager = this->m_handlerFactory.getStatisticsManager();
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
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	auto joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	if (!joinRoomRequest)
		return createErrorResponse();
	unsigned int roomId = joinRoomRequest.value().roomId;
	auto& room = roomManager.getRoom(roomId);
	if (room.getAllUsers().size() == room.getRoomMaxPlayers())
	{
		JoinRoomResponse response = { unsigned char(RESPONSES::ROOM::JOIN_ROOM_FULL) };
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
		return result;
	}
	room.addUser(m_user);
	JoinRoomResponse response = { unsigned char(RESPONSES::ROOM::JOINED_ROOM)};
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(m_user, room);
	return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo)
{
	RequestResult result;
	auto& roomManager = this->m_handlerFactory.getRoomManager();
	auto createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
	if (!createRoomRequest)
		return createErrorResponse();
	auto rooms = roomManager.getRooms();
	unsigned int roomId = rooms.size() + 1;
	RoomData roomData = { roomId,createRoomRequest.value().roomName,createRoomRequest.value().maxUsers,
						 createRoomRequest.value().questionCount,createRoomRequest.value().answerTimeout,(unsigned int)ROOM_STATUS::WAITING};
	roomManager.createRoom(m_user, roomData);
	auto& room = roomManager.getRoom(roomId);
	CreateRoomResponse response = { unsigned char(RESPONSES::ROOM::CREATED_ROOM) };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_user, room);;//needs to be new handler "RoomManagerRequestHandler" look in the state nachine uml
	return result;
}

