/*
 * File:   calculator.c
 * Author: Daniel
 *
 * Created on June 1, 2021, 12:52 AM
 */

#include <calculator.h>

int8_t get_key(int8_t key_vals[4][4]) 
{
    while (1) {
        int8_t bit_rows = 0x80; // 1000 0000
        int8_t value;
        for (int i = 0; i < 4; i++) {
            int8_t rows = ~bit_rows & 0xF0; // rows = 0111 0000
            int8_t bit_cols = 0x08; // bit_cols = 0000 1000
            LATB = rows | 0b00001111; // 0111 1111
            for (int j = 0; j < 4; j++) {
                int8_t cols = ~bit_cols & 0b00001111; // cols = 0000 0111
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

int8_t get_val(int8_t key)
{
    return key - 48;
}

int32_t calculate(int8_t operation, int8_t op_idx_1, int8_t op_idx_2, int8_t operators[]) 
{
    uint16_t operator1 = 0;
    uint16_t operator2 = 0;
    for (int8_t i = 0; i < op_idx_1; i++) {
        operator1 *= 10;
        operator1 += operators[i];
    }
    for (int8_t i = op_idx_1; i < op_idx_2; i++) {
        operator2 *= 10;
        operator2 += operators[i];
    }
    
    return get_calculation(operation, operator1, operator2);
}

int32_t get_calculation(int8_t operation, uint16_t operator_1, uint16_t operator_2) {
    switch (operation)
    {
        case '+':
            return (int32_t) operator_1 + (int32_t) operator_2;
        case '-':
            return (int32_t) operator_1 - (int32_t) operator_2;
        case '*':
            return (int32_t) operator_1 * (int32_t) operator_2;
        case '/':
            return (int32_t) operator_1 / (int32_t) operator_2;
    }
}
