#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

/// <summary>
/// handles login AND signup requests
/// </summary>
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) const override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	RequestResult login(RequestInfo reqInfo) const;
	RequestResult signup(RequestInfo reqInfo) const;

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};

