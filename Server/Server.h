#pragma once
#include "Communicator.h"
#include "IDatabase.h"
#include <thread>
class Server
{
public:
	Server();
	void run();
	~Server();
	LoginManager* getLoginManager();

private:
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};

