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

void lcd_init(void);
void lcd_clear(void);
void lcd_return_home(void);
void lcd_entry_mode(short int dir, short int shift);
void lcd_disp_control(short int disp, short int cursor, short int blink);
void lcd_cursor(short int setCursor, short int direction);
void lcd_function_set(short int DL, short int N, short int F);
void lcd_new_line(void);
void lcd_cmd(char cmd);
void lcd_rdy(void);
void lcd_write_str(char data[]);
void lcd_write_char(char data);

#endif	/* __LCD_HEADER__ */

