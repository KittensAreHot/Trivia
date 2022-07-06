#include "WSAInitializer.h"
#include "Exceptions.h"

WSAInitializer::WSAInitializer()
{
	WSADATA wsa_data = { };
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) 
		throw Exception("WSAStartup Failed");
}

WSAInitializer::~WSAInitializer()
{
	try
	{
		WSACleanup();
	}
	catch (...) {}
}
