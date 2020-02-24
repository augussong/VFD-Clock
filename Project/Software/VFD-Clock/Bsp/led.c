/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  
#include "led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_Init(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd( RCC_LED_PORT, ENABLE); 												   
		GPIO_InitStructure.GPIO_Pin = LED1_PIN|LED2_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(LEDx_PORT, &GPIO_InitStructure);	

		/* �ر�����led��	*/
		GPIO_SetBits(LEDx_PORT, LED1_PIN|LED2_PIN);
}
/*********************************************END OF FILE**********************/
