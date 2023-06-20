#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"



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
    REQUESTS requestId = static_cast<REQUESTS>(requestInfo.id);

    switch (requestId)
    {
        case REQUESTS::LOGIN:
            return login(requestInfo);
        case REQUESTS::SIGNUP:
            return signup(requestInfo);
    }
    return createErrorResponse();

}

RequestResult LoginRequestHandler::createErrorResponse()
{
    ErrorResponse err = { unsigned char(RESPONSES::ERRORS::_ERROR),"AN ERROR OCCURED." };
    Buffer msg = JsonResponsePacketSerializer::serializeResponse(err);
    return RequestResult{ msg, this->m_handlerFactory.createLoginRequestHandler() };
}

RequestResult LoginRequestHandler::login(const RequestInfo& info)
{
    //try to login
    auto request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    if (!request)
        return createErrorResponse();

    auto& loginManager = this->m_handlerFactory.getLoginManager();
    int loginStatus = loginManager.login(request.value().username, request.value().password);

    LoginResponse loginRes;
    loginRes.status = loginStatus;
    Buffer responseBuffer = JsonResponsePacketSerializer::serializeResponse(loginRes);

    if (loginStatus == int(RESPONSES::LOGIN::SUCCESS))
    {
        LoggedUser user = { request.value().username};
        RequestResult requestRes = { responseBuffer, this->m_handlerFactory.createMenuRequestHandler(user) };
        return requestRes;
    }
    RequestResult requestRes = { responseBuffer, this->m_handlerFactory.createLoginRequestHandler() };
    return requestRes;

    //std::move instead of copying, just moving the resources from one place to another

}

RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
    //try to signup
    auto request = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    if (!request)
        return createErrorResponse();
    auto& loginManager = this->m_handlerFactory.getLoginManager();
    int signupStatus = loginManager.signup(request.value().username, request.value().password, request.value().email);

    SignupResponse signupRes;
    signupRes.status = signupStatus;
    Buffer response = JsonResponsePacketSerializer::serializeResponse(signupRes);

    RequestResult requestRes = { response, this->m_handlerFactory.createLoginRequestHandler() };
    return requestRes;
}
