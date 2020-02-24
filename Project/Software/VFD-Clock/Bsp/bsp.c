#include "bsp.h"

void NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure; 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USB Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  //DS3231 INT
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
//  //HX1838 INT
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure); 
  
}

void DeBug(void)
{
	// int i = 0;
	// for(i = 0; i < WS2812_NUM; i++){
	// 	WS2812_RGB[i][0] = 127;
	// 	WS2812_RGB[i][1] = 127;
	// 	WS2812_RGB[i][2] = 127;
	// }
	// WS2812_Send_Px();

//  TIME_TypeDef SetTime;
//  SetTime.year  = 0x20;
//  SetTime.month = 0x01;
//  SetTime.date  = 0x03;
//  SetTime.hour  = 0x11;
//  SetTime.min   = 0x56;
//  SetTime.sec   = 0x0;
//  SetTime.week  = 0x05;
//  DS3231_WriteTime(&SetTime);
	
//	int i = 0;
//	for(; i < TM1803_NUM; i++){
//		TM1803_RGB[i][0] = 127;
//		TM1803_RGB[i][1] = 127;
//		TM1803_RGB[i][2] = 127;
//	}
//	TM1803_Send_Px();
}

/*
 * 函数名：BSP_Init
 * 描述  ：板级初始化
 * 输入  ：无
 * 输出  ：无
 */
void BSP_Init(void)
{
  // 在操作系统跑起来之前，不允许响应任何中断
  GLOBAL_INT_DISABLE();

  NVIC_Config();
  USART1_Init();
  USART2_Init();

  //
  USB_PreInit();
  USB_Init();

  EE_Init();
  HC595_Init();
  WS2812_Init();
  TM1803_Init();
  Beep_Init();
  LED_Init();  
  SHT2x_Init();
  DS3231_Init();
  DS3231_ReadTime(&GetTime);
  PowerCtl_Init();
  ESP8266_Init(ESP8266_RUN);
  Boost_ON();

  ClockBrightness(100);
  DeBug();
  GLOBAL_INT_ENABLE();

}

/* --------------------------------------end of file--------------------------------------- */
