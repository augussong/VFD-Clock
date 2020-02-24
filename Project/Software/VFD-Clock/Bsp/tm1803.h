#ifndef __TM1803_H
#define __TM1803_H

#include "stm32f10x.h"


#define PORT_TM1803 GPIOA
#define Pin_TM1803  GPIO_Pin_4
#define RCC_TM1803  RCC_APB2Periph_GPIOA

#define TM1803_Set    PORT_TM1803->BSRR = Pin_TM1803;
#define TM1803_Reset  PORT_TM1803->BRR  = Pin_TM1803;

//TM1803芯片级联数量
#define TM1803_NUM          2

extern u8 TM1803_RGB[TM1803_NUM][3];

void TM1803_Init(void);
void TM1803_Send_Px(void);
void TM1803_Flash_Test(void);
#endif
