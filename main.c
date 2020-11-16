/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on November 15, 2020, 3:15 PM
 */

#include "config_bits.h"
#include "lcd.h"

#define _XTAL_FREQ          1000000
#define TWO_SECONDS         2000
#define DELAY_SWEEP         150

static char key_vals[4][4] = {{1, 2, 3, 10}, {4, 5, 6, 11}, {7, 8, 9, 12}, 
    {14, 0, 15, 13}};

// Enums
enum por_dir{ output = 0, input = 1 }; //           output = 0, input = 1
enum por_ACDC{ digital = 0, analog = 1 };//         digital = 0, analog = 1
enum resistor_state{ set_ON = 0, res_ON = 1 };//    set_ON = 0, res_ON = 1
enum led_state{ led_OFF = 0, led_ON = 1 };//        led_OFF = 0, led_ON = 1
enum butto_state{pushed = 0, no_pushed = 1};//      pushed = 0, no_pushed = 1
enum exponent {bbase=2, limit=8};

// Prototype functions
void ports_init(void);

void main(void) {
    ports_init();
    LCD_init();
    while (1) {
        __delay_ms(1000);
        LCD_write("  Hello World!");
        __delay_ms(1000);
        LCD_returnHome();
    }
}

void ports_init ( void ) { //       Ports configuration
    ANSELA = 0;//                   Set PortA as digital port
    TRISA = 0; //                   Set PortA as output
    LATA = 0;
    
    ANSELD = 0;//                   Set PortD as digital port
    TRISD = 0b00001111;//           Set RD7-RD4 as output and RD3-RD0 as inputs
    LATD = 0;
    
    ANSELC = 0;//                   Set PortC as digital port
    TRISC = 0;//                    Set PortC as output
    LATC = 0;
    
    ANSELB = 0;
    TRISB = 0;
    LATB = 0;
//    INTCON2 = 0b00000000;
//    WPUB = 0b00001111;//          Ports RD3-RB0 are set as weak pull-ups
}


