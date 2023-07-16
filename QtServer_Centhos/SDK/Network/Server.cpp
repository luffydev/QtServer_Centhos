#include "Server.h"
#include "Client.h"
#include "Opcodes.h"

#include "../Logger/Logger.h"

TCPServer::TCPServer(QObject* pParent) : QTcpServer(pParent)
{
	// Init Logger
	mLogger = &Logger::instance();
	mLogger->setService("Server");

	// Init Opcode List
	OpcodeStore::instance().BuildOpcodeList();
}

void TCPServer::startServer(uint pPort)
{
	if (!isListening())
	{
		listen(QHostAddress::Any, pPort);
		*mLogger << " listening on port : " << pPort << std::endl;	
	}


}

void TCPServer::incomingConnection(qintptr pDescriptor)
{
	TcpClient* lClient = new TcpClient(pDescriptor);
	mClientList << lClient;

	*mLogger << " New client connected ! " << std::endl;

	connect(lClient, &TcpClient::disconnected, this, &TCPServer::clientDisconnected);
}

void TCPServer::clientDisconnected()
{
	*mLogger << " Client disconnected !" << std::endl;
}