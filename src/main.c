/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on November 15, 2020, 3:15 PM
 */
#include <stdint.h>
#include "config_bits.h"
#include "lcd.h"
#include "calculator.h"

#define _XTAL_FREQ          1000000

// Prototype functions
void ports_init();
void print_welcome_msg();
void print_calc_result(int32_t result);

void main(void) 
{
    const int8_t key_vals[4][4] = {{'1', '2', '3', '+'}, {'4', '5', '6', '-'}, 
        {'7', '8', '9', '*'}, {'R', '0', '#', '/'}};
    int8_t operation = 0;
    int8_t op_idx_1 = 0, op_idx_2 = 0;
    int8_t operators[14];
    
    ports_init();
    lcd_init();
    print_welcome_msg();
    
    // Main loop
    while (1) {
        int8_t key = get_key(key_vals); // waits until key gets pressed
        
        if (key == '+' || key == '-' || key == '*' || key == '/') {
            lcd_write_char(key);
            operation = key;
            op_idx_2 = op_idx_1;
        }
        else if (key == '#') {
            int32_t result = calculate(operation, op_idx_1, op_idx_2, operators);
            print_calc_result(result);
        }
        else if (key == 'R') {
           lcd_init();
           operation = 0, op_idx_1 = 0, op_idx_2 = 0;
        }
        else {
            lcd_write_char(key);
            if (operation) operators[op_idx_2++] = get_val(key);
            else           operators[op_idx_1++] = get_val(key);
        }
        __delay_ms(200);
    }   
}

void ports_init ( void ) 
{
    ANSELA = 0;//                   Set PortA as digital port
    TRISA = 0; //                   Set PortA as output
    LATA = 0;
    
    ANSELB = 0;//                   Set PortD as digital port
    TRISB = 0b00001111;//           Set RB7-RB4 as outputs and RB3-RB0 as inputs
    LATB = 0;
    INTCON2 = 0b00000000;
    WPUB = 0b00001111;;//           Ports RB3-RB0 are set as weak pull-ups
    
    
    LCD_RS_RW_E = 0;//              Set LCD control signals as digital ports
    LCD_EN_DIR=0; //                output
    LCD_RS_DIR=0; //                output
    LCD_RW_DIR=0; //                output
    LATC = 0;
    
    ANSELD = 0;
    TRISD = 0;
    LATD = 0;
}

void print_welcome_msg() {
    lcd_write_str("Basic Calc.");
    lcd_new_line();
    lcd_write_str("Ops: +, -, *, /");
    __delay_ms(5000);
    lcd_clear();
}

void print_calc_result(int32_t result) 
{
    lcd_new_line();
    
    // Shift cursor to end of disp
    for (int i = 0; i < LCD_N_CHARS; i++) {
        lcd_cursor(0, 1);//             Cursor/Disp shift   (SC->0: Cursor move, RL-> 1: Shift right)
    }
    
    lcd_entry_mode(0,0);//               Entry Mode          (ID->0: Decrement, S->0: No Display shift)
    
    int8_t is_negative = 0;
    if (result < 0)
    {
        result *= -1;
        is_negative = 1;
    }
    while (result) {
        int8_t modulo = result % 10;
        modulo += 48;
        lcd_write_char(modulo);
        result /= 10;
    }
    if (is_negative) lcd_write_char('-');
    
    lcd_disp_control(1,0,0);//           Disp Control        (D->1: Display ON, C->0: Cursor OFF, B->0: Blinking OFF)
}
