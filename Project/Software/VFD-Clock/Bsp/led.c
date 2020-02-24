/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  
#include "led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_Init(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd( RCC_LED_PORT, ENABLE); 												   
		GPIO_InitStructure.GPIO_Pin = LED1_PIN|LED2_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(LEDx_PORT, &GPIO_InitStructure);	

		/* 关闭所有led灯	*/
		GPIO_SetBits(LEDx_PORT, LED1_PIN|LED2_PIN);
}
/*********************************************END OF FILE**********************/
