#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f10x.h"
#include "bsp.h"

#define ALL_LIGHT_UP		0x00
#define ALL_LIGHT_OFF		0xFF
#define DOT		0xFE
#define ZERO	0x03
#define ONE		0x9F
#define TWO		0x25
#define THREE	0x0D
#define FOUR  0x99
#define FIVE  0x49
#define SIX   0x41
#define SEVEN 0x1F
#define EIGHT 0x01
#define NIGHT 0x09
#define ALPHABET_A  0x11
#define ALPHABET_a  0x05
#define ALPHABET_b  0xC1
#define ALPHABET_C  0x63
#define ALPHABET_c  0xE5
#define ALPHABET_d  0x85
#define ALPHABET_E  0x61
#define ALPHABET_F  0x71
#define ALPHABET_H  0x91
#define ALPHABET_L  0xE3
#define ALPHABET_O  0x03
#define ALPHABET_P  0x31
#define ALPHABET_S  0x49
#define ALPHABET_T  0x73
#define ALPHABET_t  0xE1
#define SYMBOL_NEG  0xFD

void displayTime(void);
void displayHello(void);
void displayALL(void);
void displayTemp(void);
void displayHumi(void);

#endif

