#ifndef __SERVER__
#define __SERVER__

#include <QtNetwork>
#include <iostream>
#include "../Singleton/Singleton.h"

class Logger;
class TcpClient;

class TCPServer : public QTcpServer
{
	Q_OBJECT
    DECLARE_SINGLETON(TCPServer)

public:
	void startServer(uint pPort);

private slots:
	void clientDisconnected();

protected:
	void incomingConnection(qintptr pDescriptor) override;

private:

	// ctor
	TCPServer(QObject* parent = nullptr);

	Logger* mLogger;
	QList<TcpClient*> mClientList;

};

#endif 
