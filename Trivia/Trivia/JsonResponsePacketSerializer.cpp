#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;

void to_json(json& j, const RoomData& r) {
    j = json{
        {"id", r.id},
        {"name", r.name},
        {"maxPlayers", r.maxPlayers},
        {"numOfQuestionsInGame", r.numOfQuestionsInGame},
        {"timePerQuestion", r.timePerQuestion},
        {"roomStatus", r.roomStatus}
    };
}

void to_json(json& j, const PlayerResults& r) {
    j = json{
        {"username", r.username},
        {"correctAnswerCount", r.correctAnswerCount},
        {"wrongAnswerCount", r.wrongAnswerCount},
        {"averageAnswerTime", r.averageAnswerTime},
    };
}

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
    j["rooms"] = response.rooms;
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
    buffer.push_back(char(RESPONSES::ROOM::GOT_PLAYERS_IN_ROOM));

    //LEN: 4 BYTE
    json j;
    j["status"] = RESPONSES::ROOM::GOT_PLAYERS_IN_ROOM;
    j["players"] = response.players;
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

Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    j["hasGameBegun"] = response.hasGameBegun;
    j["players"] = response.players;
    j["questionCount"] = response.questionCount;
    j["answerTimeout"] = response.status;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
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

Buffer JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));
    //LEN: 4 BYTE
    json j;
    if (response.status == unsigned char(1))
    {
        j["status"] = response.status;
        j["results"] = response.results;
    }
    else
    {
        std::cout << "GameResults ERROR: game is not finished" << std::endl;
        j["status"] = unsigned char(0);
        j["results"] = std::vector<PlayerResults>();
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

Buffer JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    j["correctAnswer"] = response.correctAnswer;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& response)
{
    Buffer buffer;
    //CODE: 1 BYTE
    buffer.push_back(char(response.status));

    //LEN: 4 BYTE
    json j;
    j["status"] = response.status;
    if (response.question == "")
    {
        j["status"] = 0;
        j["answers"] = std::vector<std::string>();
    }
    else
    {
        j["status"] = 1;
    }
    j["question"] = response.question;
    j["answers"] = response.answers;
    std::string msg = j.dump();
    addMsgLenToBuffer(buffer, msg);

    //CONTENT: X BYTES
    for (char& c : msg)
    {
        buffer.push_back(c);
    }
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveGameRoomResponse& response)
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


