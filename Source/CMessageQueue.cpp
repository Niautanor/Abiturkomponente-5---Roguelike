/*
 * CMessageQueue.cpp
 *
 *  Created on: 16.09.2011
 *      Author: Tim
 */

#include "CMessageQueue.h"

CMessageQueue::CMessageQueue()
{
	Messages = NULL;
}

bool CMessageQueue::OnInit(Uint16 X, Uint16 Y, Uint16 Max)
{
	StartX = X;
	StartY = Y;
	MaxMessages = Max;
	NumMessages = 0;

	Messages = new UNICODE_STRING[MaxMessages];
	for(int i=0;i<MaxMessages;i++)
		Messages[i] = NULL;

	return true;
}

void CMessageQueue::OnExit()
{
	Clear();
	delete[] Messages;
}

void CMessageQueue::Clear()
{
	for(int i=0;i<NumMessages;i++)
		if(Messages[i])
		{
			delete[] Messages[i];
			Messages[i] = NULL;
		}
	NumMessages = 0;
}

void CMessageQueue::AddMessage(UNICODE_STRING M)
{
	Uint16 MId = 0;//Index an dem Die Nachricht in das Message_Array geschrieben werden soll
	if(NumMessages < MaxMessages)
	{
		MId = NumMessages;
		NumMessages++;
	}
	else
	{
		delete[] Messages[0];
		for(int i=1;i<MaxMessages;i++)
			Messages[i-1] = Messages[i];
		MId = MaxMessages-1;
	}

	unsigned int MessageLen = UnicodeStrlen(M);
	Messages[MId] = new UNICODE_CHAR[MessageLen+1];
	UnicodeCpy(M, Messages[MId], MessageLen);
}


void CMessageQueue::AddMessage(const char* M)
{
	UNICODE_STRING UnicodeM = TextToUnicode(M);
	AddMessage(UnicodeM);
	delete[] UnicodeM;
}

bool CMessageQueue::PrintMessages(Screen* s)
{
	bool ret = true;
	for(int i=0;i<NumMessages;i++)
		if(Messages[i])
			if(!s->PutText(Messages[i], CColor(255,255,255),CColor(128,128,128),StartX,StartY+i))
				ret = false;
	return ret;
}
