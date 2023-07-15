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


// Surcharge spécifique pour std::endl
Logger& Logger::operator<<(std::ostream& (*manipulator)(std::ostream&))
{
    // Votre traitement pour l'opérateur << std::endl
    if (manipulator == static_cast<std::ostream & (*)(std::ostream&)>(std::endl))
    {

        if (!mService.size())
            return *this;

        std::cout << "[" << mService << "]" << " -> " << mStr.toStdString();

        mStr = "";
        // Faites quelque chose spécifique pour std::endl
        // Par exemple, enregistrez la fin de ligne dans un fichier de journal

        // Utilisez votre propre fonction de journalisation ou traitement ici
        // ...
    }

    mStream << manipulator; // Appel de l'opérateur << de std::ostream

    return *this;
}