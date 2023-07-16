#ifndef __PACKET__
#define __PACKET__

#include <QtNetwork>
#include "Opcodes.h"

class Logger;

class Packet
{
public:
	Packet(QDataStream& pStream);
	Packet(Opcodes pOpcodes);

	quint32 GetOpcode() 
	{
		return mOpcode;
	}

	quint32 GetSize()
	{
		return mSize;
	}

	QDataStream* GetStream()
	{
		return mStream;
	}

	QString ReadString()
	{
		quint32 lSize = 0;
		*mStream >> lSize;

		QByteArray lBytes;
		char* lByte = new char;

		lBytes.resize(lSize);
		
		mStream->readRawData(lByte, 1);
		qint64 lReadBytes = mStream->readRawData(lBytes.data(), lSize);

		if (!lReadBytes)
			return "";

		return QString(lBytes);
	}

private:
	quint32 mOpcode;
	quint32 mSize;
	QByteArray mByteArray;
	QDataStream *mStream;
	Logger* mLogger;
};

#endif
