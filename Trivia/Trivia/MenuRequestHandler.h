#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = default;
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);
	~MenuRequestHandler() override = default;

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& m_handlerFactory;
};
