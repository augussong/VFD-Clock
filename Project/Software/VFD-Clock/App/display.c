#include "display.h"

u8 g_displayNumTable[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NIGHT};

void displayTime(void)
{
  static u8 dotFlag = 0;
  u8 hc595[6];
  if(dotFlag){
    hc595[5] = g_displayNumTable[(GetTime.hour & 0xf0) >> 4 ];
    hc595[4] = g_displayNumTable[GetTime.hour & 0x0f] & 0xFE;
    hc595[3] = g_displayNumTable[(GetTime.min & 0xf0) >> 4];
    hc595[2] = g_displayNumTable[GetTime.min & 0x0f] & 0xFE;
    hc595[1] = g_displayNumTable[(GetTime.sec & 0xf0) >> 4];
    hc595[0] = g_displayNumTable[GetTime.sec & 0x0f];
    dotFlag = ~dotFlag;
  }
  else{
    hc595[5] = g_displayNumTable[(GetTime.hour & 0xf0) >> 4 ];
    hc595[4] = g_displayNumTable[GetTime.hour & 0x0f];
    hc595[3] = g_displayNumTable[(GetTime.min & 0xf0) >> 4];
    hc595[2] = g_displayNumTable[GetTime.min & 0x0f];
    hc595[1] = g_displayNumTable[(GetTime.sec & 0xf0) >> 4];
    hc595[0] = g_displayNumTable[GetTime.sec & 0x0f];
    dotFlag = ~dotFlag;
  }

  HC595_WriteBytes(hc595, 6);
}

void displayHello(void)
{
  u8 hc595[6];

  hc595[5] = ALPHABET_H;
  hc595[4] = ALPHABET_E;
  hc595[3] = ALPHABET_L;
  hc595[2] = ALPHABET_L;
  hc595[1] = ALPHABET_O;
  hc595[0] = DOT;

  HC595_WriteBytes(hc595, 6);
}

void displayALL(void)
{
  u8 hc595[6];

  hc595[5] = ALL_LIGHT_UP;
  hc595[4] = ALL_LIGHT_UP;
  hc595[3] = ALL_LIGHT_UP;
  hc595[2] = ALL_LIGHT_UP;
  hc595[1] = ALL_LIGHT_UP;
  hc595[0] = ALL_LIGHT_UP;

  HC595_WriteBytes(hc595, 6);
}

void displayTemp(void)
{
  u8 hc595[6];
  s8 temp0 = 0, temp1 = 0, symbol = 1;
  
  if(SHT20.TEMP_POLL >= 0){
    temp0 = (int)SHT20.TEMP_POLL;
    temp1 = (int)((SHT20.TEMP_POLL - (int)SHT20.TEMP_POLL)*100.0);
  }
  else{
    symbol = -1;
    temp0 = -(int)SHT20.TEMP_POLL;
    temp1 = -(int)((SHT20.TEMP_POLL - (int)SHT20.TEMP_POLL)*100.0);
  }
  

  hc595[5] = ALPHABET_T;
  
  if(symbol > 0)
    hc595[4] = ALL_LIGHT_OFF;
  else
    hc595[4] = SYMBOL_NEG;
  
  hc595[3] = g_displayNumTable[temp0 / 10];
  hc595[2] = g_displayNumTable[temp0 % 10] & 0xFE;
  hc595[1] = g_displayNumTable[temp1 / 10];
  hc595[0] = g_displayNumTable[temp1 % 10];

  HC595_WriteBytes(hc595, 6);
}

void displayHumi(void)
{
  u8 hc595[6];
  s8 temp0 = 0, temp1 = 0, symbol = 1;
  
  if(SHT20.HUMI_POLL >= 0){
    temp0 = (int)SHT20.HUMI_POLL;
    temp1 = (int)((SHT20.HUMI_POLL - (int)SHT20.HUMI_POLL)*100.0);
  }
  else{
    symbol = -1;
    temp0 = -(int)SHT20.HUMI_POLL;
    temp1 = -(int)((SHT20.HUMI_POLL - (int)SHT20.HUMI_POLL)*100.0);
  }
  

  hc595[5] = ALPHABET_H;
  
  if(symbol > 0)
    hc595[4] = ALL_LIGHT_OFF;
  else
    hc595[4] = SYMBOL_NEG;
  
  hc595[3] = g_displayNumTable[temp0 / 10];
  hc595[2] = g_displayNumTable[temp0 % 10] & 0xFE;
  hc595[1] = g_displayNumTable[temp1 / 10];
  hc595[0] = g_displayNumTable[temp1 % 10];
  
  HC595_WriteBytes(hc595, 6);
}
