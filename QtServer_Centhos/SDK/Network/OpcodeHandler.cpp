#include "Packet.h"
#include "Client.h"
#include "../Logger/Logger.h"
#include "OpcodeHandler.h"

OpcodeHandler::OpcodeHandler()
{
	mLogger = &Logger::instance();
	mLogger->setService("Packet");
}

void OpcodeHandler::Handle_NULL(Packet& pPacket, TcpClient* pSocket)
{
	*mLogger << " RECV Handle_NULL Packet ... Abort." << std::endl;
}

void OpcodeHandler::Handle_Connect_Challenge_Request(Packet& pPacket, TcpClient* pSocket)
{
	*mLogger << " RECV Handle_Connect_Challenge_Request Packet ..." << std::endl;

	QString lUsername = pPacket.ReadString();
	QString lPassword = pPacket.ReadString();

	*mLogger << " Recv login : " << lUsername << " and password : " << lPassword << std::endl;
}
