/*
 * File:   lcd.c
 * Author: Daniel
 *
 * Created on January 10, 2021, 3:11 AM
 */

#include "lcd.h"

void lcd_init(void) {
    lcd_clear(); //                     Clear Display
    lcd_function_set(1, 1, 0); //        Function Set (DL->1: 8 bit data line, N->1: 2 data lines, F->0: 5x8 font)
    lcd_disp_control(1, 1, 1); //        Disp Control (D->1: Display ON, C->1: Cursor ON, B->1: Blinking ON)
    lcd_entry_mode(1, 0);//              Entry Mode   (ID->1: Increment, S->0: No display shift)
}

void lcd_clear(void) {
    lcd_cmd(0b00000001);
}

void lcd_return_home(void) {
    lcd_cmd(0b00000010);
}

void lcd_entry_mode(short int ID, short int SH) {
    lcd_cmd(0b00000100 | ID << 1 | SH);
}

void lcd_disp_control(short int D, short int C, short int B) {
    lcd_cmd(0b00001000 | D << 2 | C << 1 | B);
}

void lcd_cursor(short int SC, short int RL) {
    lcd_cmd(0b00010000 | SC << 3 | RL << 2);
}

void lcd_function_set(short int DL, short int N, short int F) {
    lcd_cmd(0b00100000 | DL << 4 | N << 3 | F << 2);
}

void lcd_new_line() {
    lcd_cmd(0xC0);
}

void lcd_cmd (char cmd) {
    lcd_rdy();
    LCD_RS=0;
    LCD_RW=0;
    LCD_EN=1;
    Nop();
    LCD_DATA_W = cmd;
    Nop();
    LCD_EN=0;
    Nop();
}   

void lcd_rdy (void) {
    char busy = 0x80; // 0b10000000
    LCD_DATA_DIR = 0b11111111;//    LCD data bus as input
    LCD_RS = 0; //                  Select IR register
    LCD_RW = 1; //                  Set read mode
    
    // Wait until busy flag bit is cleared
    while (busy) {
        LCD_EN = 1;
        Nop();
        busy = LCD_DATA_R & 0x80;// Check busy flag bit 0x80 = 0b10000000
        Nop();
        LCD_EN = 0;
        Nop();
    }
    
    LCD_DATA_DIR = 0b00000000;//    LCD data bus as output
}

void lcd_write_str(char data[]) {
    lcd_rdy();
    LCD_RS = 1;    
    LCD_RW = 0;
    
    // Write each character in string
    short int length = strlen(data);
    for (int i = 0; i < length; i++){
        LCD_EN = 1;
        Nop();
        LCD_DATA_W = data[i];
        Nop();
        LCD_EN = 0;
        Nop();
        __delay_ms(50);
    }
}

void lcd_write_char(char data) {
    lcd_rdy();
    LCD_RS = 1;
    LCD_RW = 0;
    
    LCD_EN = 1;
    Nop();
    LCD_DATA_W = data;
    Nop();
    LCD_EN = 0;
    Nop();
}


