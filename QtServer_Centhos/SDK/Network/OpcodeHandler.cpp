#include "../Logger/Logger.h"
#include "../Utils/Utils.h"

#include "Packet.h"
#include "Client.h"
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

	*pSocket->GetLogger() << " RECV Handle_Connect_Challenge_Request Packet ..." << std::endl;

	QString lUsername = pPacket.ReadString();
	QString lPasswordHash = QString(pPacket.ReadBytes().toHex()).toUpper();

	*pSocket->GetLogger() << " Recv login : " << lUsername << " and password hash : " << lPasswordHash << std::endl;

	QString lKey = Utils::instance().GenerateString(256);

	Packet lPacket(Opcodes::SMSG_CONNECT_CHALLENGE_RESPONSE);
	
	*lPacket.GetStream() << (quint8)SessionStatus::STATUS_LOGGED;
	lPacket.WriteString(lKey);

	*pSocket->GetLogger() << " Sending Key : " << lKey << std::endl;

	pSocket->Send(lPacket.Build());
}
