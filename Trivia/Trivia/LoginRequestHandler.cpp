#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

using std::unique_ptr;
using std::make_unique;

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{

}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    if (requestInfo.id == int(REQUESTS::LOGIN) || requestInfo.id == int(REQUESTS::SIGNUP))
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) 
{
    Buffer msg;
    RequestResult requestRes;
    switch (REQUESTS(requestInfo.id))
    {
        case REQUESTS::LOGIN:
            requestRes = login(requestInfo);
            break;
        case REQUESTS::SIGNUP:
            requestRes = signup(requestInfo);
            break;
        default:
            ErrorResponse err = { "Request isn't relevant" };
            msg = JsonResponsePacketSerializer::serializeResponse(err);
            requestRes = { msg, this->m_handlerFactory.createLoginRequestHandler() };
            break;
    }
    return requestRes;
}

RequestResult LoginRequestHandler::login(const RequestInfo& info)
{
    //try to login
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    int loginStatus = this->m_handlerFactory.getLoginManager().login(request.username, request.password);

    LoginResponse loginRes;
    loginRes.status = loginStatus;
    Buffer responseBuffer = JsonResponsePacketSerializer::serializeResponse(loginRes);

    unique_ptr<IRequestHandler> handler;
    if (loginStatus == int(RESPONSES::LOGIN::SUCCESS))
    {
        RequestResult requestRes = { responseBuffer, this->m_handlerFactory.createMenuRequestHandler() };
        return requestRes;
    }
    RequestResult requestRes = { responseBuffer, this->m_handlerFactory.createLoginRequestHandler() };
    return requestRes;
    
    //std::move instead of copying, just moving the resources from one place to another
    
}

RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
    //try to signup
    SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    int signupStatus = this->m_handlerFactory.getLoginManager().signup(request.username, request.password, request.email);

    SignupResponse signupRes;
    signupRes.status = signupStatus;
    Buffer response = JsonResponsePacketSerializer::serializeResponse(signupRes);



    RequestResult requestRes = { response, this->m_handlerFactory.createLoginRequestHandler() };
    return requestRes;
}
