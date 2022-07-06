#include "Server.h"
#include "SqliteDatabase.h"


Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(m_database), m_communicator(m_handlerFactory) {}


Server::~Server() 
{
	if (this->m_database)
		delete this->m_database;
}

LoginManager* Server::getLoginManager()
{
	return &(this->m_handlerFactory.getLoginManager());
}


void Server::run()
{
	std::thread(&Communicator::startHandleRequests, &(this->m_communicator)).detach();
}
