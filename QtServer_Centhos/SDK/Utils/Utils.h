#ifndef __UTILS__
#define __UTILS__

#include <QtCore>
#include "../Singleton/Singleton.h"

#define DEFAULT_STR_LEN   15

class Utils 
{
	DECLARE_SINGLETON(Utils)

   public:
	   QString GenerateString(uint pLen = DEFAULT_STR_LEN);

   private:
	   Utils(){}

};

#endif
