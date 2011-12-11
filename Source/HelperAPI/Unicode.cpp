/*
 * Unicode.cpp
 *
 *  Created on: 20.09.2011
 *      Author: Tim
 */

#include "HelperAPI/Unicode.h"

UNICODE_STRING TextToUnicode(const char* Text)
{
	unsigned int len = strlen(Text)+1;
	Uint16* ret = new UNICODE_CHAR[len];
	for(unsigned int i=0;i<len;i++)
		ret[i] = Text[i];
	ret[len-1] = '\0';
	return ret;
}

UNICODE_STRING UnicodeCpy(UNICODE_STRING src, UNICODE_STRING dst, Uint16 len)
{
	if(!src | !dst | (len<=0))
		return NULL;
	return (UNICODE_STRING)memcpy(dst, src, len*sizeof(UNICODE_CHAR));
}

unsigned int UnicodeStrlen(UNICODE_STRING s)
{
	unsigned int ret = 0;
	while(s[ret] != '\0')
		ret++;
	return ret;
}
