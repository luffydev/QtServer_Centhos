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
	Logger& operator <<(uint pValue);
	Logger& operator <<(std::ostream& (*manipulator)(std::ostream&));

private:
	Logger() : mStream(std::cout) {}
	std::string mService;
	QString mStr;
	std::ostream& mStream;
};

#endif 