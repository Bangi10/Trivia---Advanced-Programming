#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    std::string data(buffer.begin(), buffer.end()); 


    return LoginRequest();
}
