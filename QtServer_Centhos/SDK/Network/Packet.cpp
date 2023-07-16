#include "../Logger/Logger.h"
#include "Packet.h"

Packet::Packet(QDataStream& pStream) : mStream(&pStream), mOpcode(Opcodes::MSG_NONE), mSize(0)
{

	mLogger = &Logger::instance();
	mLogger->setService("Packet");

	mStream->setByteOrder(QDataStream::LittleEndian);
	
	// get our opcode
	*mStream >> mOpcode;

	// get our packet size
	*mStream >> mSize;

	// get our packet timestamp
	*mStream >> mTime_t;
}

Packet::Packet(Opcodes pOpcode) : mSize(0)
{
	mLogger = &Logger::instance();
	mLogger->setService("Packet");

	mOpcode = pOpcode;
	mStream = new QDataStream(&mByteArray, QIODevice::WriteOnly);
}

QByteArray Packet::Build()
{
	QByteArray lBytesArray;
	QDataStream lStream(&lBytesArray, QIODevice::WriteOnly);

	quint64 lTime_t = QDateTime::currentSecsSinceEpoch();

	// Build our packet header
	lStream << (quint32)GetOpcode();
	lStream << (quint32)(mByteArray.size() + (sizeof(quint32) * 2) + sizeof(quint64));
	lStream << (quint64)lTime_t;

	*mLogger << " Sending Timestamp : " << lTime_t << std::endl;

	lBytesArray.append(mByteArray);

	return lBytesArray;
}