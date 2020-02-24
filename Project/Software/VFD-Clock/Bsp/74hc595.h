#ifndef __74HC595_H
#define __74HC595_H

#include "stm32f10x.h"

// 74HC595
#define HC595_PORT  GPIOB
#define HC595_RCC   RCC_APB2Periph_GPIOB
#define HC595_DATA  GPIO_Pin_3    // serial data input, pin14
#define HC595_SCLK  GPIO_Pin_4    // shift register clock input, pin11
#define HC595_RCLK  GPIO_Pin_5     // storage register clock input, pin12
// #define HC595_OE    GPIO_Pin_3     // output enable,active low,pin13

// #define HC595_OFF()   GPIO_SetBits(HC595_PORT,HC595_OE); 
// #define HC595_ON()    GPIO_ResetBits(HC595_PORT,HC595_OE); 

//其他引脚连接
//Reset(PIN10)=VCC
//SQh(PIN9)(级联输出端)=下一个595的输入端
//程序里没有把OE接地，例程需要手动接地！
void HC595_Init(void);
void HC595_Input(uint8_t byte);
void HC595_Latch(void);
void HC595_WriteBytes(u8 *data,u8 num);
#endif
