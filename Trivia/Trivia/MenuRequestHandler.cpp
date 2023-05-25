#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const RequestHandlerFactory& handlerFactory)
{
	this->m_handlerFactory = handlerFactory;
}
