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

bool CMessageQueue::OnInit(Uint16 Max, Uint16 ML)
{
	MaxMessages = Max;
	NumMessages = 0;

	MessageLifetime = ML;

	Messages = new SMessage[MaxMessages];
	for(int i=0;i<MaxMessages;i++) {
		Messages[i].Text = NULL;
		Messages[i].Lifetime = 0;
	}

	return true;
}

void CMessageQueue::OnExit()
{
	Clear();
	for(Uint16 i=0;i<MaxMessages;i++) {
		delete[] Messages[i].Text;
		Messages[i].Text = NULL;
		Messages[i].Visible = false;
		Messages[i].Lifetime = 0;
	}
	delete[] Messages;
}

/**
 * @function: löscht alle Nachrichten
 **/
void CMessageQueue::Clear()
{
	for(int i=0;i<NumMessages;i++)
	{
		if(Messages[i].Text)
		{
			delete[] Messages[i].Text;
			Messages[i].Text = NULL;
			Messages[i].Visible = false;
			Messages[i].Lifetime = 0;
		}
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
		delete[] Messages[0].Text;//Lösche die Erste Nachricht
		for(int i=1;i<MaxMessages;i++) { //Und shifte die anderen nachrichten nach oben
			Messages[i-1].Text = Messages[i].Text;
			Messages[i-1].Visible = Messages[i].Visible;
			Messages[i-1].Lifetime = Messages[i].Lifetime;
		}
		MId = MaxMessages-1; //Die Neue Nachricht wird am Ende angehängt
	}
	//Nachricht Einfügen
	unsigned int MessageLen = strlen(M); //Textlänge für strcpy
	Messages[MId].Text = new char[MessageLen+1];
	strcpy(Messages[MId].Text, M);  //Text kopieren
	Messages[MId].Visible = true; //Sichtbarkeit festlegen
	Messages[MId].Lifetime = MessageLifetime; //Lebenszeit festlegen
}

bool CMessageQueue::PrintMessages(Screen* s, Uint16 StartX, Uint16 StartY, Uint16 MaxMessagesOnScreen, bool ArchiveMode)
{
	bool ret = true;
	Sint16 RenderY = 0;
	Uint16 FirstRenderedMessage = (NumMessages - MaxMessagesOnScreen > 0) ? NumMessages - MaxMessagesOnScreen : 0; //wenn es mehr Nachrichten gibt als angezeigt werden sollen wird die zuerst gerenderte Nachricht auf einen wert > 0 gesetzt

	if(ArchiveMode)
	{
		for(int i=FirstRenderedMessage;i<NumMessages;i++)
			if(Messages[i].Text)
				if(!s->PutText(Messages[i].Text, CColor(255,255,255),CColor(128,128,128),StartX,StartY+RenderY++))//RenderY++ -> RenderY (wird direkt danach inkrementiert)
					ret = false;
	}
	else
	{
		for(int i=FirstRenderedMessage;i<NumMessages;i++)
			if(Messages[i].Text && Messages[i].Visible)
				if(!s->PutText(Messages[i].Text, CColor(255,255,255),CColor(128,128,128),StartX,StartY+RenderY++))//RenderY++ -> RenderY (wird direkt danach inkrementiert)
					ret = false;
	}

	return ret;
}

/**
 * @function: Prüft für alle Nachrichten die Lebenszeit und löscht sie wenn sie abgelauften ist
 **/
void CMessageQueue::Tick()
{
	if(NumMessages == 0) return;

	Uint16 OldNumMessages = NumMessages;
	for(Uint16 i=0;i<OldNumMessages;i++)
	{
		if(Messages[i].Lifetime == 0 && Messages[i].Text != NULL) {
			Messages[i].Visible = false;
		}
		else
			Messages[i].Lifetime--;
	}
}
