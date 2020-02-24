#ifndef  __BSP_H__
#define  __BSP_H__

#include "stdio.h"
#include "stm32f10x.h"
#include "os_cfg_app.h"
#include "cpu.h"
#include "SysTick.h"
#include "usart1.h"
#include "usart2.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_istr.h"
#include "led.h"
#include "ds3231.h"
#include "beep.h"
#include "ws2812b.h"
#include "tm1803.h"
#include "sht2x.h"
#include "eeprom.h"
#include "74hc595.h"
#include "power.h"
#include "bootloader.h"
#include "esp8266.h"

#define GLOBAL_INT_ENABLE()		__set_PRIMASK(0);
#define GLOBAL_INT_DISABLE()	__set_PRIMASK(1);

void BSP_Init(void);
void DeBug(void);

#endif /* __BSP_H__ */



