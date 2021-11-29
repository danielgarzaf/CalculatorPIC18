/*
 * File: lcd.h
 * Author: Daniel Garza 
 * Comments: Header file for LCD interfacing
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __CALC_HEADER
#define	__CALC_HEADER__

int8_t get_key(int8_t key_vals[4][4]);
int8_t get_val(int8_t key);
int32_t calculate(int8_t operation, int8_t op_idx_1, int8_t op_idx_2, int8_t operators[]);

#endif	/* __CALC_HEADER__ */

