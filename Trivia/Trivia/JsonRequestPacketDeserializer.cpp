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
    json jData = json::parse(data);
    return SignupRequest({ jData["username"], jData["password"], jData["email"] });
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
    json jData = json::parse(data);
    return GetPlayersInRoomRequest({ jData["roomId"] });
}

JoinRoomRequest JsonRequestPacketDeserializer::JoinRoomRequestdeserializeJoinRoomRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
    json jData = json::parse(data);
    return JoinRoomRequest({ jData["roomId"] });
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
    json jData = json::parse(data);
    return CreateRoomRequest({ jData["roomName"],  jData["maxUsers"], 
                               jData["questionCount"], jData["answerTimeout"]});
}
