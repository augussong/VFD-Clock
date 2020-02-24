#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"        
								
#define TIME_PERIOD_CNT	2999
								
void Beep_Init(void);
void Beep_Amp(u8 percent);

#endif
