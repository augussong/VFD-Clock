#ifndef __ESP8266_H
#define __ESP8266_H

#include "bsp.h"

typedef enum{
  ESP8266_DOWNLOAD = 0, 
  ESP8266_RUN
}ESP8266_MODE;

#define ESP8266_ON()  GPIO_SetBits(GPIOB, GPIO_Pin_11);
#define ESP8266_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_11);

#define ESP8266_RunMode()  GPIO_SetBits(GPIOB, GPIO_Pin_10);
#define ESP8266_DownloadMode()  GPIO_ResetBits(GPIOB, GPIO_Pin_10);

void ESP8266_Mode(ESP8266_MODE mode);
void ESP8266_Reset(void);
void ESP8266_Init(ESP8266_MODE mode);

#endif
