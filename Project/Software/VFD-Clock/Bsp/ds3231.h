#ifndef __DS3231_H
#define __DS3231_H

#include "stm32f10x.h"
#include "stdio.h"
#include "i2c.h"

#define DS3231_INT_RCC  							RCC_APB2Periph_GPIOA
#define DS3231_INT_PORT 							GPIOA
#define DS3231_INT_PIN  							GPIO_Pin_15
#define DS3231_INT_EXTI_PORT_SOURCE 	GPIO_PortSourceGPIOA
#define DS3231_INT_EXTI_PIN_SOURCE 		GPIO_PinSource15 
#define DS3231_INT_EXTI_LINE 					EXTI_Line15
//*****************DS3231*******************
#define   DS3231_ADDRESS  	0xD0//默认为写模式，+1为读模式

#define   DS3231_SecReg  		0x00
#define   DS3231_MinReg  		0x01
#define   DS3231_HourReg  	0x02
#define   DS3231_WeekReg  	0x03
#define   DS3231_DateReg  	0x04
#define   DS3231_MonReg  		0x05
#define   DS3231_YearReg  	0x06

#define   DS3231_A1SecReg  	0x07
#define   DS3231_A1MinReg  	0x08
#define   DS3231_A1HourReg  0x09
#define   DS3231_A1WeekReg  0x0A

#define   DS3231_A2MinReg  	0x0B
#define   DS3231_A2HourReg 	0x0C
#define   DS3231_A2WeekReg 	0x0D

#define   DS3231_ControlReg 0x0E
#define   DS3231_StatusReg  0x0F
#define   DS3231_AOReg  		0x10
#define   DS3231_TEMP_H_Reg 0x11
#define   DS3231_TEMP_L_Reg 0x12

typedef struct
{
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char week;
	unsigned char date;
	unsigned char month;
	unsigned char year;
}TIME_TypeDef;

extern TIME_TypeDef SetTime,GetTime,Alarm;

void DS3231_Init(void);
void DS3231_INT_EXTI_Switch(FunctionalState flag);

void DS3231_WriteTime(TIME_TypeDef* time);
void DS3231_ReadTime(TIME_TypeDef* time);
u8 DS3231_ReadReg(u8 Reg);
u8 DS3231_WriteReg(u8 Reg,u8 data);
void DS3231_SetSecondAlarm(void);
void DS3231_ReadAll(void);

#endif
