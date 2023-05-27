#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
using json = nlohmann::json;

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(RESPONSES::_ERROR));

    //LEN: 4 BYTE
    json j;
    j["message"] = response.message;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

void JsonResponsePacketSerializer::addMsgLenToBuffer(Buffer& buffer, const std::string& msg)
{
    int len = msg.length();
    int shiftBy = 24;
    
    //convert int into 4 chars
    for (int i = 0; i < sizeof(int); i++)
    {
        buffer.push_back((len >> shiftBy) & 0xFF);
        shiftBy -= 8;
    }
}
