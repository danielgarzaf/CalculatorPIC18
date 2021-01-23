/*
 * File: lcd.h
 * Author: Daniel Garza 
 * Comments: Header file for LCD interfacing
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __LCD_HEADER__
#define	__LCD_HEADER__

#include <xc.h> // include processor files - each processor file is guarded.
#include <string.h>

#define _XTAL_FREQ          1000000
#define LCD_RS_RW_E         ANSELC
#define LCD_DATA_R          PORTD
#define LCD_DATA_W          LATD
#define LCD_DATA_DIR        TRISD
#define LCD_RS              PORTCbits.RC2
#define LCD_RS_DIR          TRISCbits.TRISC2
#define LCD_RW              PORTCbits.RC1
#define LCD_RW_DIR          TRISCbits.TRISC1
#define LCD_EN              PORTCbits.RC0
#define LCD_EN_DIR          TRISCbits.TRISC0
#define LCD_N_CHARS         15

void LCD_init(void);
void LCD_clear(void);
void LCD_returnHome(void);
void LCD_entryMode(short int dir, short int shift);
void LCD_dispControl(short int disp, short int cursor, short int blink);
void LCD_cursor(short int setCursor, short int direction);
void LCD_functionSet(short int DL, short int N, short int F);
void LCD_newLine(void);
void LCD_cmd(char cmd);
void LCD_rdy(void);
void LCD_writeStr(char data[]);
void LCD_writeChar(char data);

#endif	/* __LCD_HEADER__ */

