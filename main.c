/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on November 15, 2020, 3:15 PM
 */

#include "config_bits.h"
#include "lcd.h"
#include <stdint.h>

#define _XTAL_FREQ          1000000
#define TWO_SECONDS         2000
#define DELAY_SWEEP         150

// Enums
enum port_dir{ output = 0, input = 1 }; //           output = 0, input = 1
enum port_ACDC{ digital = 0, analog = 1 };//         digital = 0, analog = 1
enum resistor_state{ set_ON = 0, res_ON = 1 };//    set_ON = 0, res_ON = 1
enum led_state{ led_OFF = 0, led_ON = 1 };//        led_OFF = 0, led_ON = 1
enum butto_state{pushed = 0, no_pushed = 1};//      pushed = 0, no_pushed = 1
enum exponent {bbase=2, limit=8};


// Prototype functions
void ports_init(void);
void printCalcResult(int32_t result);
char getKey(char key_vals[4][4]);
char getVal(char key);
int32_t calculate(char operation, char opIdx1, char opIdx2, char operators[]);


void main(void) 
{
    // Constants, Variables and Setup
    static char key_vals[4][4] = {{'1', '2', '3', '+'}, {'4', '5', '6', '-'}, {'7', '8', '9', '*'}, 
        {'R', '0', '#', '/'}};
    char operation = 0;
    char opIdx1, opIdx2 = 0;
    char operators[14];
    ports_init();
    LCD_init();
    
    // Main loop
    while (1) {
        // Waits until a key is pressed
        char key = getKey(key_vals);
        char val = getVal(key);
        
        if (key == '+' || key == '-' || key == '*' || key == '/') {
            LCD_writeChar(key);
            operation = key;
            opIdx2 = opIdx1;
        }
        else if (key == '#') {
            int32_t result = calculate(operation, opIdx1, opIdx2, operators);
            printCalcResult(result);
        }
        else if (key == 'R') {
           LCD_init();
           operation = 0, opIdx1 = 0, opIdx2 = 0;
        }
        else {
            LCD_writeChar(key);
            if (operation) operators[opIdx2++] = val;
            else           operators[opIdx1++] = val;
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


void printCalcResult(int32_t result) 
{
    LCD_newLine();
    
    // Shift cursor to end of disp
    for (int i = 0; i < LCD_N_CHARS; i++) {
        LCD_cursor(0, 1);//             Cursor/Disp shift   (SC->0: Cursor move, RL-> 1: Shift right)
    }
    
    LCD_entryMode(0,0);//               Entry Mode          (ID->0: Decrement, S->0: No Display shift)
    char negativeFlag = 0;
    if (result < 0)
    {
        result *= -1;
        negativeFlag = 1;
    }
    while (result) {
        char modulo = result % 10;
        modulo += 48;
        LCD_writeChar(modulo);
        result /= 10;
    }
    if (negativeFlag) LCD_writeChar('-');
    
    LCD_dispControl(1,0,0);//           Disp Control        (D->1: Display ON, C->0: Cursor OFF, B->0: Blinking OFF)
}


char getKey(char key_vals[4][4]) 
{ 
    while (1) {
        char bit_rows = 0b10000000;
        char value;
        for (int i = 0; i < 4; i++) {
            char rows = ~bit_rows & 0b11110000; // 0111 0000
            char bit_cols = 0b00001000;
            LATB = rows | 0b00001111; // 0111 1111
            for (int j = 0; j < 4; j++) {
                char cols = ~bit_cols & 0b00001111; // 0000 0111
                value = rows | cols;
                if (PORTB == value) {
                    LATA = (PORTB & 0b00001111) << 4;
                    return key_vals[i][j];
                }
                bit_cols = bit_cols >> 1;
            }
            bit_rows = bit_rows >> 1;
        }
    }
}


char getVal(char key)
{
    return key - 48;
}


int32_t calculate(char operation, char opIdx1, char opIdx2, char operators[]) 
{
    uint32_t operator1 = 0;
    uint32_t operator2 = 0;
    for (char i = 0; i < opIdx1; i++) {
        operator1 *= 10;
        operator1 += operators[i];
    }
    for (char i = opIdx1; i < opIdx2; i++) {
        operator2 *= 10;
        operator2 += operators[i];
    }
    switch (operation)
    {
        case '+':
            return operator1 + operator2;
        case '-':
            if (operator2 > operator1){
                int32_t result = operator2 - operator1;
                result *= -1;
                return result;
            }
            else
                return operator1 - operator2;
        case '*':
            return operator1 * operator2;
        case '/':
            return operator1 / operator2;
    }
}