#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer buffer;
    buffer.push_back(char(RESPONSES::ERROR));
    std::string msg = "{message: “ERROR”}";
    addMsgLenToBuffer(buffer, msg);
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    return Buffer();
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    return Buffer();
}

void JsonResponsePacketSerializer::addMsgLenToBuffer(Buffer& buffer, const std::string& msg)
{
    int len = msg.length();
    int shiftBy = 24;
    
    for (int i = 0; i < sizeof(int); i++)
    {
        buffer.push_back((len >> shiftBy) & 0xFF);
        shiftBy -= 8;
    }
}
