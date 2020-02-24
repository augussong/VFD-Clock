#include "power.h"

void PowerCtl_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

  //升压开关
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void CloseRGB(void)
{
  
}

// 时钟亮度调节
// 输入：0 - 100
void ClockBrightness(u8 brightness)
{
  int i = 0;
  if(brightness>100)
    return;

  for(; i < TM1803_NUM; i++){
  //		TM1803_RGB[i][0] = (u8)(brightness / 100.0*255);
  //		TM1803_RGB[i][1] = (u8)(brightness / 100.0*255);
  //		TM1803_RGB[i][2] = (u8)(brightness / 100.0*255);
    TM1803_RGB[i][0] = 255;
    TM1803_RGB[i][1] = 254;
    TM1803_RGB[i][2] = 254;
  }
  TM1803_Send_Px();
}

