#ifndef __CLIENT__
#define __CLIENT__

#include <QtNetwork>

class Logger;

class TcpClient : public QObject
{
	Q_OBJECT

    public: 
		TcpClient(qintptr pDescriptor);

		void generateUniqID();
		QString getUniqID();

		Logger* GetLogger();

		void Send(QByteArray pPacket);

    private slots:
	    void onRecvData();
		void onDisconnect();

signals:
	    void disconnected();

    private: 
		Logger* mLogger;
		QTcpSocket* mSocket;
		QString mUniqID;
};

#endif 