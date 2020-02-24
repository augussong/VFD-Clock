#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

#define RCC_LED_PORT 	RCC_APB2Periph_GPIOB
#define LEDx_PORT			GPIOB
#define LED1_PIN			GPIO_Pin_14
#define LED2_PIN			GPIO_Pin_15

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LEDx_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LEDx_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LEDx_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LEDx_PORT,LED2_PIN)


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)				{p->BSRR=i;}			//����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)				{p->BRR=i;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE()		digitalToggle(LEDx_PORT,LED1_PIN)
#define LED1_OFF()			digitalHi(LEDx_PORT,LED1_PIN)
#define LED1_ON()				digitalLo(LEDx_PORT,LED1_PIN)

#define LED2_TOGGLE()		digitalToggle(LEDx_PORT,LED2_PIN)
#define LED2_OFF()			digitalHi(LEDx_PORT,LED2_PIN)
#define LED2_ON()				digitalLo(LEDx_PORT,LED2_PIN)

void LED_Init(void);

#endif /* __LED_H */
