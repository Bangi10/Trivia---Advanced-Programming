#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    if (requestInfo.id == int(REQUESTS::LOGIN) || requestInfo.id == int(REQUESTS::SIGNUP))
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) 
{
    RequestResult result;
    result.newHandler.reset(this);
    if (isRequestRelevant(requestInfo))
    {
        if (requestInfo.id == int(REQUESTS::LOGIN)) {
            LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
            result.response.push_back(char(RESPONSES::LOGIN_Y));
        }
        if (requestInfo.id == int(REQUESTS::SIGNUP)) {
            SignupRequest signup = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
            result.response.push_back(char(RESPONSES::SIGNUP_Y));
        }
    }
    return result;
}

