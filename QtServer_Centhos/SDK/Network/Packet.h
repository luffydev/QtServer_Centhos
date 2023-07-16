#ifndef __PACKET__
#define __PACKET__

#include <QtNetwork>
#include <iostream>
#include "Opcodes.h"

class Logger;

class Packet
{
public:
	Packet(QDataStream& pStream);
	Packet(Opcodes pOpcodes);

	QByteArray Build();

	quint32 GetOpcode() 
	{
		return mOpcode;
	}

	quint32 GetSize()
	{
		return mSize;
	}

	quint64 GetTimestamp()
	{
		return mTime_t;
	}

	QDataStream* GetStream()
	{
		return mStream;
	}

	/* ---------------------------
	          Reader part
	   ---------------------------
	*/

	QString ReadString()
	{
		QByteArray lBytes = ReadBytes();

		if (!lBytes.size())
			return "";

		return QString(lBytes);
	}

	QByteArray ReadBytes()
	{
		quint32 lSize = 0;
		*mStream >> lSize;

		QByteArray lBytes;
		lBytes.resize(lSize);

		qint64 lReadBytes = mStream->readRawData(lBytes.data(), lSize);

		if (!lReadBytes)
			return QByteArray();

		return lBytes;
	}

	/* ---------------------------
			  Writter part
	   ---------------------------
	*/

	void WriteBytes(QByteArray pBytes)
	{
		if (!mStream)
			return;

		*mStream << (QByteArray)pBytes;
	}

	void WriteString(QString pStr)
	{
		WriteBytes(pStr.toUtf8());
	}



private:
	quint32 mOpcode;
	quint32 mSize;
	quint64 mTime_t;
	QByteArray mByteArray;
	QDataStream *mStream;
	Logger* mLogger;
};

#endif
