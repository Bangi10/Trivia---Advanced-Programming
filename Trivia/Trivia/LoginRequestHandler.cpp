#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

using std::unique_ptr;
using std::make_unique;

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    if (requestInfo.id == int(REQUESTS::LOGIN) || requestInfo.id == int(REQUESTS::SIGNUP))
        return true;
    return false;
}

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{

}

LoginRequestHandler::~LoginRequestHandler()
{

}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) 
{
    Buffer msg;
    RequestResult requestRes;
    requestRes.newHandler.reset(this);
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
    bool loginSuccess = this->m_handlerFactory.getLoginManager().login(request.username, request.password);

    LoginResponse loginRes;
    unique_ptr<IRequestHandler> handler;
    if (loginSuccess)
    {
        loginRes.status = int(RESPONSES::LOGIN_Y);
        handler = make_unique<MenuRequestHandler>();
    }
    else
    {
        loginRes.status = int(RESPONSES::LOGIN_N);
        handler = make_unique<LoginRequestHandler>();
    }
    Buffer response = JsonResponsePacketSerializer::serializeResponse(loginRes);
    RequestResult requestRes = { response, handler };
    return RequestResult;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
    //try to login
    SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    bool signupSuccess = this->m_handlerFactory.getLoginManager().signup(request.username, request.password, request.email);

    SignupResponse signupRes;
    unique_ptr<IRequestHandler> handler = make_unique<LoginRequestHandler>();
    if (signupSuccess)
    {
        signupRes.status = int(RESPONSES::SIGNUP_Y);
    }
    else
    {
        signupRes.status = int(RESPONSES::SIGNUP_N);
    }
    Buffer response = JsonResponsePacketSerializer::serializeResponse(signupRes);
    RequestResult requestRes = { response, handler };
    return RequestResult;
}
