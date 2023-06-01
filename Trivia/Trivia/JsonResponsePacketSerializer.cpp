#include "JsonResponsePacketSerializer.h"
using json = nlohmann::json;

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(RESPONSES::ERRORS::_ERROR));

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

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    for (auto& it : response.rooms)//adding rooms to json
    {
        j += json{
        {"id", it.id},
        {"name", it.name},
        {"maxPlayers", it.maxPlayers},
        {"numOfQuestionsInGame", it.numOfQuestionsInGame},
        {"timePerQuestion", it.timePerQuestion},
        {"roomStatus", it.roomStatus}
        };
    }
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(RESPONSES::ROOM::GET_PLAYER_IN_ROOM));

    //LEN: 4 BYTE
    json j;
    j["status"] = RESPONSES::ROOM::GET_PLAYER_IN_ROOM;
    j["PlayersInRoom"] = response.players;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const getHighScoreResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    j["statistics"] = response.statistics;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const getPersonalStatusResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    j["UserStatistics"] = response.statistics;
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

