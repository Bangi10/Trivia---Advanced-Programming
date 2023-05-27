#include "RequestHandlerFactory.h"

std::unique_ptr<IRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
    return std::unique_ptr<IRequestHandler>();
}
