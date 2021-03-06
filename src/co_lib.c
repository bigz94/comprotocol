/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_lib.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Hilfsfunktionen und Emuriationen
*
* Dieses Dokument enthaelt Funktionen und Definitionen von Makros die auch
* ausserhalb dieser Bibliothek genutzt werden können.
*/

/************************************************************************/

#include "../headers/co_lib.h"

/************************************************************************/
/* Variablen															*/
/************************************************************************/

uint8_t* co_MsgCache_cache;
uint8_t co_MsgCache_position;

/************************************************************************/
/* f_co_MsgCache_release()												*/
/************************************************************************/
void f_co_MsgCache_release()
{
	free(co_MsgCache_cache);
}

/************************************************************************/
/* f_co_MsgCache_init()													*/
/************************************************************************/
void f_co_MsgCache_init()
{
	co_MsgCache_cache = malloc(CO_MAXMESSAGEBUFFERSIZE * sizeof(uint8_t));
	co_MsgCache_position = 0;
}

/************************************************************************/
/* f_co_MsgCache_append(value)											*/
/************************************************************************/
uint8_t f_co_MsgCache_append(uint8_t value)
{
	if(co_MsgCache_position < CO_MAXMESSAGEBUFFERSIZE)
		co_MsgCache_cache[co_MsgCache_position++] = value;
				
	return co_MsgCache_position;
}

/************************************************************************/
/* f_co_MsgCache_setPosition(position)									*/
/************************************************************************/
void f_co_MsgCache_setPosition(uint8_t position)
{
	co_MsgCache_position = position < CO_MAXMESSAGEBUFFERSIZE ? position : CO_MAXMESSAGEBUFFERSIZE - 1;
}

/************************************************************************/
/* f_co_MsgCache_getPosition(position)									*/
/************************************************************************/
void f_co_MsgCache_getPosition()
{
	return co_MsgCache_position;
}

/************************************************************************/
/* f_co_MsgCache_reset()												*/
/************************************************************************/
void f_co_MsgCache_reset()
{
	co_MsgCache_position = 0;
}

/************************************************************************/
/* f_co_MsgCache_getStart()												*/
/************************************************************************/
uint8_t* f_co_MsgCache_getStart()
{
	return co_MsgCache_cache;
}

/************************************************************************/