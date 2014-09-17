/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_document.h
* @author Emanuel Foster, Lucien Zuercher
* @date 1. Jan. 2014
* @brief Konstanten und Globale Veriablen fuer Einstellungen.
*
* Dieses Dokument enthaelt verschiedene Konstanten und globale Variablen,
* die frei zum Einstellen sind.
*/
#ifndef _CO_DOCUMENT_H
# define _CO_DOCUMENT_H

/****************************************************************************
* Einstellungen
****************************************************************************/

/** Einfache Einstellung **/

/**
 * Einzigartige Identifikationsnummer
 * Min: 0
 * Max: 255
 */
#define ID 1

/**
 * Setzt den normalzustand des Controllers
 * 0 : Lesen
 * 1 : Schreiben
 */
#define WRITE 1

#endif /* _CO_DOCUMENT_H */

/****************************************************************************/