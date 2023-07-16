#include "Logger.h"

void Logger::setService(std::string pService)
{
	mService = pService;
}

Logger& Logger::operator<<(const char* pValue)
{
    mStr.append(pValue);
	return *this;
}

Logger& Logger::operator<<(uint pValue)
{
    mStr.append(QString::number(pValue));
    return *this;
}

Logger& Logger::operator<<(QString pValue)
{
    mStr.append(pValue);
    return *this;
}


Logger& Logger::operator<<(std::ostream& (*manipulator)(std::ostream&))
{
    if (manipulator == static_cast<std::ostream & (*)(std::ostream&)>(std::endl))
    {

        if (!mService.size())
            return *this;

        QFile lFile = CreateDir();

        if (!lFile.open(QIODevice::Append | QIODevice::Text))
        {
            std::cout << "[ERROR] -> Unable to open log file " << std::endl;
            return *this;
        }

        std::cout << "[" << mService << "]" << " -> " << mStr.toStdString();

        QTextStream textStream_;
        textStream_.setDevice(&lFile);
        
        textStream_ << GetFormatedDate() << "[" << mService.c_str() << "]" << " -> " << mStr << Qt::endl;
        textStream_.flush();


        mStr = "";
    }

    mStream << manipulator; 

    return *this;
}