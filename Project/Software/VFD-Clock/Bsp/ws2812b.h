#ifndef __WS1812_H
#define __WS1812_H

#include "stm32f10x.h"
#include <string.h>
#include "stdio.h"
#include "math.h"
#include "ds3231.h"

/****WARNING!***
 * WS2812_Send_Px()ִ��ʱ���ܱ���ϣ�ע����ж�Ƕ������
*/
#define PORT_WS2812 GPIOB
#define Pin_WS2812  GPIO_Pin_1
#define RCC_WS2812  RCC_APB2Periph_GPIOB

#define WS2812_Set()    PORT_WS2812->BSRR = Pin_WS2812;
#define WS2812_Reset()  PORT_WS2812->BRR  = Pin_WS2812;

//��������
#define WS2812_NUM 			6
#define MAX_TUBE_NUM		6
#define MAX_LIGHT_LEVEL 255

//������
typedef enum{
	TUBE0 = 0,
	TUBE1,
  TUBE2,
  TUBE3,
  TUBE4,
  TUBE5,
}TubeNum_e;

//��ɫ��
typedef enum{
	GREEN = 0,
	RED = 1,
  BLUE = 2,
}BaseColor_e;

//ģʽѡ��-mode
typedef enum{
	SINGLECOLOR = 0,
	MULTICOLOR = 1,
  RAINBOW = 2,
}ColorMode_e;

//��Чѡ��-state
typedef enum{
	EFFECTS_ON=0,
	EFFECTS_OFF=1,
	RGB_OFF=2
}EffectState_e;

//RGB�ṹ��
typedef struct{
  u8 R;
  u8 G;
  u8 B;
  ColorMode_e mode;//ɫ��ģʽ��mode=0-->��ɫģʽ��mode=1-->��ɫģʽ
  EffectState_e state;//��Чѡ�� 0���������� 1�������� 2��Ϩ��
}RGB_TypeDef;
//�б�ʾ�����������б�ʾRGB��Ϣ

extern __IO u8 WS2812_RGB[WS2812_NUM][3];
extern __IO u8 RcdMAX_RGB[WS2812_NUM][3];
extern __IO RGB_TypeDef RGB_Msg;
extern u8 RainBowstate[WS2812_NUM];

void WS2812_Init(void);
void WS2812_Send_Px(void);
void WS2812_Breath(void);
void WS2812_Refresh(u8 R,u8 G,u8 B);

#endif
