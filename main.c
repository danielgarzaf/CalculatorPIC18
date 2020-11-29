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
enum por_dir{ output = 0, input = 1 }; //           output = 0, input = 1
enum por_ACDC{ digital = 0, analog = 1 };//         digital = 0, analog = 1
enum resistor_state{ set_ON = 0, res_ON = 1 };//    set_ON = 0, res_ON = 1
enum led_state{ led_OFF = 0, led_ON = 1 };//        led_OFF = 0, led_ON = 1
enum butto_state{pushed = 0, no_pushed = 1};//      pushed = 0, no_pushed = 1
enum exponent {bbase=2, limit=8};


// Prototype functions
void ports_init(void);
void printCalcResult(long int result);

void main(void) {
    static char key_vals[4][4] = {{1, 2, 3, 10}, {4, 5, 6, 11}, {7, 8, 9, 12}, 
        {14, 0, 15, 13}};
    ports_init();
    LCD_init();
    
    // Main loop
    while (1) {
        LCD_writeStr("1234*5678");
        LCD_newLine();
        
        // Write result at lower right corner of LCD
        int32_t result = 1234L*5678;      
        printCalcResult(result);
        
        LCD_init();
    }
}

void ports_init ( void ) {
    ANSELA = 0;//                   Set PortA as digital port
    TRISA = 0; //                   Set PortA as output
    LATA = 0;
    
    ANSELB = 0;//                   Set PortD as digital port
    TRISB = 0b00001111;//           Set RB7-RB4 as output and RB3-RB0 as inputs
    LATB = 0;
    
    LCD_RS_RW_E = 0;//              Set LCD control signals as digital ports
    LCD_EN_DIR=0; //                output
    LCD_RS_DIR=0; //                output
    LCD_RW_DIR=0; //                output
    LATC = 0;
    
    ANSELD = 0;
    TRISD = 0;
    LATD = 0;
//    INTCON2 = 0b00000000;
//    WPUB = 0b00001111;;//           Ports RD3-RB0 are set as weak pull-ups
}

void printCalcResult(long int result) {
    // Shift cursor to end of disp
    for (int i = 0; i < LCD_N_CHARS; i++) {
        LCD_cursor(0, 1);//             Cursor/Disp shift   (SC->0: Cursor move, RL-> 1: Shift right)
    }
    LCD_entryMode(0,0);//               Entry Mode          (ID->0: Decrement, S->0: No Display shift)
    while (result) {
        char modulo = result % 10;
        modulo += 48;
        LCD_writeChar(modulo);
        result /= 10;
    }    
    LCD_dispControl(1,0,0);//           Disp Control        (D->1: Display ON, C->0: Cursor OFF, B->0: Blinking OFF)
    __delay_ms(2000);
}

