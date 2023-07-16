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
}

Packet::Packet(Opcodes pOpcode) : mSize(0)
{
	mLogger = &Logger::instance();
	mLogger->setService("Packet");

	mOpcode = pOpcode;
	mStream = new QDataStream();
}