#ifndef __POWER_H
#define __POWER_H

#include "stm32f10x.h"
#include "tm1803.h"

#define Boost_ON()  GPIO_SetBits(GPIOA, GPIO_Pin_7);
#define Boost_OFF()  GPIO_ResetBits(GPIOA, GPIO_Pin_7);

void PowerCtl_Init(void);
void CloseRGB(void);
void ClockBrightness(u8 brightness);

#endif
