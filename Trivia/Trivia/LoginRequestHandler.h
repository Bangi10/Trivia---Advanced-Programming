#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler() override = default;

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;

	RequestResult createErrorResponse();
private:
	RequestHandlerFactory& m_handlerFactory;

	RequestResult login(const RequestInfo& info);
	RequestResult signup(const RequestInfo& info);
};