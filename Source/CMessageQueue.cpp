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

	Messages = new char*[MaxMessages];
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


void CMessageQueue::AddMessage(const char* M)
{
	Uint16 MId = 0;//Index an dem Die Nachricht in das Message_Array geschrieben werden soll
	if(NumMessages < MaxMessages)
	{
		MId = NumMessages;//Nachricht in die Letzte stelle des Nachrichtenarrays schreiben
		NumMessages++;//Es gibt eine Nachricht mehr
	}
	else //Ansonsten töte die erste nachricht und lösche ihre gesamte Fammilie
	{
		delete[] Messages[0];
		for(int i=1;i<MaxMessages;i++)
			Messages[i-1] = Messages[i];
		MId = MaxMessages-1;
	}
	unsigned int MessageLen = strlen(M);
	Messages[MId] = new char[MessageLen+1];
	strcpy(Messages[MId], M);
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
