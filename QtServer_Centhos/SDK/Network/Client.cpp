#include "../Logger/Logger.h"
#include "../Utils/Utils.h"

#include "Client.h"
#include "Packet.h"
#include "Opcodes.h"
#include "OpcodeHandler.h"


TcpClient::TcpClient(qintptr pDescriptor)
{

	mLogger = &Logger::instance();
	mLogger->setService("Client");

	generateUniqID();

	mSocket = new QTcpSocket();
	mSocket->setSocketDescriptor(pDescriptor);

	connect(mSocket, &QTcpSocket::readyRead, this, &TcpClient::onRecvData);
	connect(mSocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnect);
}

void TcpClient::Send(QByteArray pPacket)
{
	mSocket->write(pPacket);
}

void TcpClient::onRecvData()
{
	*mLogger << " Recv data !!!!" << std::endl;

	// if received data less 2 uint32 (opcode + size)
	if (mSocket->bytesAvailable() < ( (sizeof(quint32) * 2) + sizeof(quint64) ))
		return;

	
	QDataStream lStream(mSocket);

	Packet lPacket(lStream);
	

	*mLogger << " TEST : " << mSocket->bytesAvailable() << std::endl;

	*mLogger << " RECV OPCODE : " << lPacket.GetOpcode() << " SIZE : " << lPacket.GetSize() << std::endl;

	OpcodeStore* lStore = &OpcodeStore::instance();

	if (!lStore->OpcodeExist(lPacket.GetOpcode()))
	{
		*mLogger << " RECV unhandled packet with opcode : " << lPacket.GetOpcode() << " and size : " << lPacket.GetSize() << std::endl;
		mSocket->flush();
		
		return;
	}

	OpcodeStruct lStruct = lStore->GetOpcodeData(lPacket.GetOpcode());

	*mLogger << " RECV " << lStruct.name << " opcode handle it !" << std::endl;

	OpcodeHandler* lHandler = new OpcodeHandler();

	//we call our function
	(lHandler->*lStruct.handler)(lPacket, this);

	mSocket->readAll();
}

Logger* TcpClient::GetLogger()
{
	return mLogger;
}

void TcpClient::onDisconnect()
{
	emit(disconnected());
}

void TcpClient::generateUniqID()
{
	QString lRandomString = Utils::instance().GenerateString();
	mUniqID = lRandomString;
}

QString TcpClient::getUniqID()
{
	return mUniqID;
}