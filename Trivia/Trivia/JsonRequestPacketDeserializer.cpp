#include "JsonRequestPacketDeserializer.h"
using json = nlohmann::json;


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    std::string data(buffer.begin(), buffer.end()); 
    json jData;
    std::stringstream(data) >> jData;
    return LoginRequest({ jData["username"], jData["password"] });
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
    std::string data(buffer.begin(), buffer.end());
    json jData;
    std::stringstream(data) >> jData;
    return SignupRequest({ jData["username"], jData["password"], jData["email"]});
}
