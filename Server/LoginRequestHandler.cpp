#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
//#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Prefixes.h"
#include "Exceptions.h"
#include <mutex>

#define SUCCESS 1
#define FAILED 1

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory),  m_loginManager(loginManager)
{}

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo) const
{
	return reqInfo.requestId == Prefix::LOGINREQUEST || reqInfo.requestId == Prefix::SIGNUPREQUEST;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	// Function returns the response (serialized), with the next handler. (can be login, error, etc.)
	try
	{
		if (reqInfo.requestId == Prefix::LOGINREQUEST) {
			return this->login(reqInfo);
		}
		if (reqInfo.requestId == Prefix::SIGNUPREQUEST) {
			return this->signup(reqInfo);
		}
	}
	catch (...)
	{
		return {
			JsonResponsePacketSerializer::serializeResponse({ "Invalid data" }),
			nullptr
		};
	}
	throw Exception("Request has not been implemented yet");
}

RequestResult LoginRequestHandler::login(RequestInfo reqInfo) const
{
	LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
	
	std::unique_lock<std::mutex> loginManagerMutex(this->m_handlerFactory.getLoginManagerMutex());
	LoginResponse loginResp = {
		static_cast<unsigned int>(this->m_loginManager.login(req.username, req.password))
	};
	loginManagerMutex.unlock();

	if (loginResp.status == SUCCESS) return {
		JsonResponsePacketSerializer::serializeResponse(loginResp),
		reinterpret_cast<IRequestHandler*>(this->m_handlerFactory.createMenuRequestHandler(req.username))
	};

	else return {
		JsonResponsePacketSerializer::serializeResponse(loginResp),
		nullptr
	};
 }

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo) const
{
	SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
	std::unique_lock<std::mutex> loginManagerMutex(this->m_handlerFactory.getLoginManagerMutex());
	SignupResponse signupResp = {
		static_cast<unsigned int>(this->m_loginManager.singup(req.username, req.email, req.password))
	};
	loginManagerMutex.unlock();

	if (signupResp.status == SUCCESS) return {
		JsonResponsePacketSerializer::serializeResponse(signupResp),
		reinterpret_cast<IRequestHandler*>(this->m_handlerFactory.createMenuRequestHandler(req.username))
	};
	else return {
		JsonResponsePacketSerializer::serializeResponse(signupResp),
		nullptr
	};
}
