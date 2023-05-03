#include "LoginRequestHandler.h"

enum class REQUESTS { LOGIN = 100, SIGNUP = 110 };

bool LoginRequestHandler::isRequestRelevant(const RequestInfo* requestInfo) const
{
    if (requestInfo->id == int(REQUESTS::LOGIN) || requestInfo->id == int(REQUESTS::LOGIN))
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo* requestInfo) const 
{
    //?
}
