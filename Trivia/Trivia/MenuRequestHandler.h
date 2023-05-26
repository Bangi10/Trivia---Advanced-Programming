#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
	public:
		MenuRequestHandler(const RequestHandlerFactory& handlerFactory);
		~MenuRequestHandler() override = default;
	private:
		RequestHandlerFactory& m_handlerFactory;
};
