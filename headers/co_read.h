/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens ver�ffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_read.h
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Funktionen und Hilfsfunktionen zum Lesen einer Verbindung.
*
* Die hier vorhandenen Funktionen werden genutzt um eine Verbindung
* gebgebenen Port abzuhoeren. Bit f�r Bit werden diese Informationen
* nach einem gegebenen Tackt eingelesen und in auf Cache geschrieben.
*/

#ifndef _CO_READ_H
#define _CO_READ_H

/****************************************************************************
* Includes
****************************************************************************/

# include "co.h"

/****************************************************************************
* Makros
****************************************************************************/


/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/

enum CO_READ_STATUS{
	CO_READ_WAITING = 0,
	CO_READ_HEADER = 1,
	CO_READ_MESSAGE = 2,
	CO_READ_CHECKSUM = 3
};

/**
 * Groesser der header struktur in bytes
 */
#define CO_READ_HEADERSIZE = 4

/**
 * Protokoll Messageheader-Struktur definition
 */
typedef struct {
	uint8_t Initialisation;	/**< Initialisierung */
	uint8_t Target;	/**< Ziel Addresse */
	uint8_t Source;	/**< Von Addresse */
	uint8_t Info; /**< Befehl- oder Textinformationen */
} t_co_msg_header;

/**
 * Die Protokoll struktur einer gesendeten Text-message
 */
typedef struct {
	t_co_msg_header header;
	uint8_t* text;
	uint8_t checksum; /** < Checksumme der gesendeten message - muss auf letzes byte zeigen */
} t_co_msg_text;

/**
 * Die Message struktur f�r ein gesendeter command
 */
typedef struct {
	uint8_t checksum; /** < Checksumme der gesendeten message  */
} t_co_msg_command;

/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * bit lesen
 * @param byte byte eingelesen
 */
void f_co_readbit(uint8_t byte);

/**
 * byte bearbeiten und dem buffer hinzufuegen
 * @param byte Das eingelesene byte
 */
void f_co_processbyte(uint8_t byte);

void f_co_processHeader();

void f_co_checkValid(uint8_t byte);

void f_co_processChecksum();

#endif /* _CO_WRITE_H */

/****************************************************************************/