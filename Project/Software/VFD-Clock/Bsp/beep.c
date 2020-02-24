#include "beep.h"

void Beep_Delay(u32 j)
{
  u32 i=0;
  for(;j>0;j--)
    for(;i<0x1ffff;i++);
}

//调节PWM占空比
void Beep_Amp(u8 percent)
{
	if(percent > 100)
		return;
	
	TIM3->CCR1 = (u8)(TIME_PERIOD_CNT * (float)percent / 100.0);
}

void Beep_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure; 

	/* 设置TIM3CLK 为 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
  ----------------------------------------------------------------------- */
	
  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = TIME_PERIOD_CNT;      //当定时器从0计数到2999，即为3000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 8;	    //设置预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频(这里用不到)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = TIME_PERIOD_CNT / 2;	   	 //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1
	
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//使能TIM3预装载
	TIM_ARRPreloadConfig(TIM3, ENABLE);								//使能TIM3重载寄存器ARR
	
	Beep_Amp(0);
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);           //使能定时器3	
}


