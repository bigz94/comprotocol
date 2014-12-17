/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens ver�ffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_read.c
* @author Emanuel Foster, Lucien Zuercher
* @date 10. Dez. 2014
* @brief Funktionen und Hilfsfunktionen zum schreiben einer Verbindung.
*
* Die hier vorhandenen Funktionen werden genutzt um auf einer Verbindung
* des gebgebenen Port zu senden. Bit f�r Bit werden diese Informationen
* nach einem gegebenen Tackt geschrieben.
*/

#include "../headers/co.h"

void f_co_write_Text(char* p_sText){
	cPointerSendByte = 0;
	
	f_co_write_ProtocollHeader(2);
	
	char nLength = strlen(p_sText);
	char cCommand = (1<<7) & nLength;
	//Command and L?nge senden
	f_co_write_Byte(cCommand);
	
	char* Text_save = p_sText;

	bool controll = true;
	//Solange bis kein Zeichen mehr vorhanden
	while(*p_sText != '\0' && controll){
		controll = f_co_write_Byte(*(p_sText));
		p_sText++;
	}
	if(controll)
	{
		f_co_write_Byte(checksum);
		cPaketGroesse = cPointerSendByte;
		cPointerSendByte = 0;
		cPositionBit = 0b10000000;
		bSending = 1;
	}
	//Falls controll-bit != gesendetes-bit
	else
	{
		//Eigene ID als ms warten
		_delay_ms(10);
		//Text erneut senden
		f_co_write_Text(Text_save);
	}
}

void f_co_write_Command(unsigned char p_cCommand){
	cPointerSendByte = 0;
	
	f_co_write_ProtocollHeader(2);
	bool controll = f_co_write_Byte(p_cCommand);
	if(controll)
	{
		f_co_write_Byte(checksum);
		cPaketGroesse = cPointerSendByte;
		cPointerSendByte = 0;
		cPositionBit = 0b10000000;
		bSending = 1;
	}
	//Falls controll-bit != gesendetes-bit
	else
	{
		//Eigene ID als ms warten
		_delay_ms(10);
		//Text erneut senden
		f_co_write_Command(p_cCommand);
	}
}

bool f_co_write_Byte(char p_cByte){	
	//Checksum XOR Verkn�pfen
	checksum ^= p_cByte;
	//Senden vorbereiten (In Array laden)
	sSendByte[cPointerSendByte] = p_cByte;
	cPointerSendByte++;

	return true;
}

bool f_co_write_Controll(char p_cBitControll){
	//Bit einlesen
	DDRA = 0xFE;
	char bit_read = ~PINA;
	
	if(p_cBitControll == 0){
		if(bit_read == 0){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(bit_read == 1){
			return true;
		}
		else{
			return false;
		}
	}
}

void f_co_write_ProtocollHeader(char destination_id){
	
	DDRD = 0x04;

	checksum = 0;

	char source_id = ID;
	
	bSending = 1;
	//4-mal 1/0 senden f?r Beginn
	f_co_write_Byte(0b10101010);
	
	//HEADER Daten senden
	f_co_write_Byte(destination_id);
	f_co_write_Byte(source_id);
}