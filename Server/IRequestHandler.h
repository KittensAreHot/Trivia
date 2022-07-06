#pragma once
#include "Request.h"

class IRequestHandler;

typedef struct RequestResult {
	Buffer response;
	IRequestHandler* newHandler = nullptr;
} RequestResult;	

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo reqInfo) const = 0;
	virtual RequestResult handleRequest(RequestInfo reqInfo) = 0;

};