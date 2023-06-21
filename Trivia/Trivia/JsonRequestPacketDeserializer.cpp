#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
using json = nlohmann::json;


std::optional<LoginRequest> JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
	try
	{
		json jData = json::parse(data);
		return LoginRequest({ jData["username"], jData["password"] });
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::optional<SignupRequest> JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
	try
	{
		json jData = json::parse(data);
		return SignupRequest({ jData["username"], jData["password"], jData["email"] });
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::optional<GetPlayersInRoomRequest> JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());

	try
	{
		json jData = json::parse(data);
		return GetPlayersInRoomRequest({ jData["roomId"] });
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::optional<JoinRoomRequest> JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());

	try
	{
		json jData = json::parse(data);
		return JoinRoomRequest({ jData["roomId"] });
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::optional<CreateRoomRequest> JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());

	try
	{
		json jData = json::parse(data);
		return CreateRoomRequest({ jData["roomName"],  jData["maxUsers"],
								   jData["questionCount"], jData["answerTimeout"] });
	}
	catch (...)
	{
		return std::nullopt;
	}
}

std::optional<SubmitAnswerRequest> JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(const std::vector<unsigned char>& buffer)
{
	std::string data(buffer.begin(), buffer.end());

	try
	{
		json jData = json::parse(data);
		return SubmitAnswerRequest({ jData["answer"], jData["correctAnswer"]});
	}
	catch (...)
	{
		return std::nullopt;
	}
}

