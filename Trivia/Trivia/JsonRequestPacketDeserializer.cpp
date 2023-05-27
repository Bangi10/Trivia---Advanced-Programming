#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
using json = nlohmann::json;


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
    json jData = json::parse(data);
    return LoginRequest({ jData["username"], jData["password"] });
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& buffer)
{
    std::string data(buffer.begin(), buffer.end());
    json jData = json::parse(data);
    return SignupRequest({ jData["username"], jData["password"], jData["email"] });
}
