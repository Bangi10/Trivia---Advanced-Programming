#include "LoginRequestHandler.h"

enum class REQUESTS { LOGIN = 100, SIGNUP = 110 };

bool LoginRequestHandler::isRequestRelevant(const RequestInfo* requestInfo) const
{
    if (requestInfo->id == int(REQUESTS::LOGIN) || requestInfo->id == int(REQUESTS::SIGNUP))
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo* requestInfo) const 
{
    RequestResult result;
    if (isRequestRelevant(requestInfo))
    {
        if (requestInfo->id == int(REQUESTS::LOGIN)) {
            //?
        }
        if (requestInfo->id == int(REQUESTS::SIGNUP)) {
            //?
        }
    }
    return result;
}
