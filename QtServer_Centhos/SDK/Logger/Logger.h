#ifndef __LOGGER__
#define __LOGGER__

#include <QtCore>
#include <iostream>
#include "../Singleton/Singleton.h"

class Logger 
{

	DECLARE_SINGLETON(Logger)


public:
	void setService(std::string pService = "Core");
    
	Logger& operator <<(const char* pValue);
	Logger& operator <<(QString pValue);
	Logger& operator <<(uint pValue);
	Logger& operator <<(std::ostream& (*manipulator)(std::ostream&));

	QFile  CreateDir()
	{
		QDateTime lDateTime = QDateTime::currentDateTime();
		QString lDirName = lDateTime.toString("dd-MM-yyyy");

		QDir lLogDir("logs/" + lDirName);

		if (!lLogDir.exists())
			lLogDir.mkpath(".");

		return QFile(lLogDir.absoluteFilePath("output.log"));

	}

	QString GetFormatedDate()
	{
		QDateTime dateTime = QDateTime::currentDateTime();
		return dateTime.toString("[yyyy-MM-dd hh:mm:ss] ");
	}

private:
	Logger() : mStream(std::cout) {}
	std::string mService;
	QString mStr;
	std::ostream& mStream;
};

#endif 