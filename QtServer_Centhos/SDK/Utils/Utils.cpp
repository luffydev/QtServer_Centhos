#include "Utils.h"

#include <QRandomGenerator>
#include <QString>

QString Utils::GenerateString(uint pLen)
{
	const QString lPossibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	const int lPossibleCharactersCount = lPossibleCharacters.length();

	QString lRandomString;
	lRandomString.reserve(pLen);

	for (int lI = 0; lI < pLen; ++lI)
	{
		int lRandomIndex = QRandomGenerator::global()->bounded(lPossibleCharactersCount);
		lRandomString.append(lPossibleCharacters.at(lRandomIndex));
	}

	return lRandomString;
}