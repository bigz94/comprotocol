/****************************************************************************
 * Copyright (C) 2012 by Matteo Franchin                                    *
 *                                                                          *
 * This file is part of Box.                                                *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file co.h
 * @author Lucien
 * @date 3.7.2014
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 */


#ifndef CO_H_
#define CO_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

volatile extern uint8_t co_byte;		// used to safe byte while reading
volatile extern uint8_t co_status;	// status of while reading

extern uint8_t *co_cachpos;	// contains current position in message buffer



extern uint8_t co_curinput; // current input remove later
// REMOVE later used to output switch
extern uint8_t co_debug_var;

// Temporary Variable can be used everywhere
extern uint8_t tmp;

//////////////////////////////////////////////////////////////////////////
// Simple bit operations
//////////////////////////////////////////////////////////////////////////
#define SET_BIT(var, bit) ((var) |= (1 << bit))
#define CLEAR_BIT(var, bit) ((var) &= ~(1 << bit))

#define TOGGLE_BIT(var, bit) ((var) ^= (1 << bit))

#define ISSET_BIT(var, bit) ((var) & (1 << bit))
#define ISCLEAR_BIT(var, bit) (!ISSET_BIT(var, bit))

//////////////////////////////////////////////////////////////////////////
// genutzte status flags
enum 
{
	READING,
	PROCESS,
	LASTREADBIT,
	DELAY,
	MESSAGEREADING,
	MESSAGEREAD,
	ERROR
};

//////////////////////////////////////////////////////////////////////////
// einstellungen
#define CO_USEDTIMER TOIE1
#define CO_TIMERSPEED 3
#define CO_PINREADING 2

#define CO_MESSAGEIDENTIFIER 0b10101010

/*
#define WAITING 1 << 0
#define READING 1 << 1
#define WRITING 1 << 2
#define BYTEWAITING 1 << 3 // neues byte empfangen und bereit
#define BITREAD 1 << 7
/*
struct CO_STATUS_TYPE
{
	READING = WAITING;
	WRITING = READ;
	WAITING << 2;	
};*/

void f_co_inputchange();
void f_co_initializeOverflowInterrupt();

void f_co_init_waitmode();

void f_co_readbit();
void f_co_processbyte(uint8_t byte);

void f_co_update();

#endif /* CO_H_ */