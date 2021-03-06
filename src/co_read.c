/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_read.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Funktionen und Hilfsfunktionen zum Lesen einer Verbindung.
*
* Die hier vorhandenen Funktionen werden genutzt um eine Verbindung
* gebgebenen Port abzuhoeren. Bit für Bit werden diese Informationen
* nach einem gegebenen Tackt eingelesen und in auf Cache geschrieben.
*/

/************************************************************************/

#include "../headers/co.h"

/************************************************************************/
/* Variables                                                            */
/************************************************************************/

uint8_t co_read_msglength = CO_MAXMESSAGEBUFFERSIZE;

/************************************************************************/
/* f_co_init_waitmode()													*/
/************************************************************************/
void f_co_init_waitmode()
{
	// I-Flag temporaer speichern
	tmp = SREG;
	cli();
	
	// setzten des INT0 um bei einer Aenderung das
	// lesen zu beginnen
	// INT0 (PD2) auf fallende flanke reagieren
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	GICR |= (1 << INT0);
	
	// timer fuers erste deaktivieren, da noch keine Nachricht erhalten
	TIMSK &= ~(1 << CO_USEDTIMER);
	
	SREG = tmp;
	
	// co_byte wieder zuruecksetzen
	co_byte = 0x01;
	
	f_co_resetReader();
}

/************************************************************************/
/* f_co_processbyte(byte)                                               */
/************************************************************************/
void f_co_processbyte(uint8_t byte)
{
	f_co_MsgCache_append(byte);
}

/************************************************************************/
/* f_co_processHeader()                                                 */
/************************************************************************/
void f_co_processHeader() {
	co_read_msglength = f_co_getMsglength();	
	
	SET_BIT(co_status, HEADERPROCESSED);
}

/************************************************************************/
/* f_co_processHeader()                                                 */
/************************************************************************/
uint8_t f_co_getMsglength() {
	t_co_msg_header* msgheader = ((t_co_msg_header*)f_co_MsgCache_getStart());
	
	uint8_t msglength = CO_READ_HEADERSIZE + 1;
	if(ISSET_BIT(msgheader->Info, 7)){
		msglength += (msgheader->Info & 0x7f);
	}
	return msglength;
}

/************************************************************************/
/* f_co_resetReader()													*/
/************************************************************************/
void f_co_resetReader() {
	co_status = 0x00;
	co_read_msglength = 0xff;
}

/************************************************************************/
/* f_co_processMsg()                                                    */
/************************************************************************/
void f_co_processMsg() {
	f_co_resetReader();
	SET_BIT(co_status, MESSAGEREAD);
}

/************************************************************************/
/* f_co_read_update()                                                   */
/************************************************************************/
void f_co_read_update() {
	if(co_MsgCache_position >= CO_READ_HEADERSIZE){
		if(ISCLEAR_BIT(co_status, HEADERPROCESSED))
			f_co_processHeader();
		else if(co_MsgCache_position > co_read_msglength)
			f_co_processMsg();
		
	}
}

/************************************************************************/
/* f_co_readbit(byte)                                                   */
/************************************************************************/
void f_co_readbit(bool bit)
{
	bool tmp = co_byte & (1 << 7);
	
	co_byte = co_byte << 1;
	co_byte |= bit;
	
	// check if message is real
	if(ISCLEAR_BIT(co_status, MESSAGEREADING))
	{
		if(CO_MESSAGEIDENTIFIER == co_byte)
		{
			SET_BIT(co_status, MESSAGEREADING);
			f_co_MsgCache_setPosition(0);
			tmp = 1;
		}
	}
	
	// reads byte
	if(ISSET_BIT(co_status, MESSAGEREADING) && tmp)
	{
		// ganzes byte gelesen
		f_co_processbyte(co_byte);
		co_byte = 0x01;
	}
	
	// information abspeichern fuer status
	if(bit)
		SET_BIT(co_status, LASTREADBIT);
	else
		CLEAR_BIT(co_status, LASTREADBIT);
}

/************************************************************************/