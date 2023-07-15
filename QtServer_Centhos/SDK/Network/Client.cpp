#include "../Logger/Logger.h"
#include "Client.h"
#include <QRandomGenerator>
#include <QString>

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

void TcpClient::onRecvData()
{
	*mLogger << " Recv data !!!!" << std::endl;
	
	QDataStream lPacket(mSocket);
	lPacket.setByteOrder(QDataStream::LittleEndian);

	quint32 lOpcode, lSize = 0;

	lPacket >> lOpcode;
	lPacket >> lSize;

	*mLogger << " TEST : " << mSocket->bytesAvailable() << std::endl;

	*mLogger << " RECV OPCODE : " << lOpcode << " SIZE : " << lSize << std::endl;


}

void TcpClient::onDisconnect()
{
	emit(disconnected());
}

void TcpClient::generateUniqID()
{
	const uint lStringLen = 15;
	const QString lPossibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	const int lPossibleCharactersCount = lPossibleCharacters.length();

	QString lRandomString;
	lRandomString.reserve(lStringLen);

	for (int lI = 0; lI < lStringLen; ++lI)
	{
		int lRandomIndex = QRandomGenerator::global()->bounded(lPossibleCharactersCount);
		lRandomString.append(lPossibleCharacters.at(lRandomIndex));
	}

	mUniqID = lRandomString;
}

QString TcpClient::getUniqID()
{
	return mUniqID;
}