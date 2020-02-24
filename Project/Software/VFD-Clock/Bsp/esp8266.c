#include "esp8266.h"

void ESP8266_Delay(void)
{
  int i = 0x7ffff;
  while(i--);
}

void ESP8266_Mode(ESP8266_MODE mode)
{
  if(mode == ESP8266_RUN)
  {
    ESP8266_RunMode();
  }
  else
  {
    ESP8266_DownloadMode();
  }
}

void ESP8266_Reset(void)
{
  ESP8266_OFF();
  ESP8266_Delay();
  ESP8266_ON();
}

void ESP8266_Init(ESP8266_MODE mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  //WiFi运行模式选择
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  //WiFi供电开关
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  ESP8266_Mode(mode);
  ESP8266_Reset();
}
