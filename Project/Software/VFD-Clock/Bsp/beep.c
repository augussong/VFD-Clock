#include "beep.h"

void Beep_Delay(u32 j)
{
  u32 i=0;
  for(;j>0;j--)
    for(;i<0x1ffff;i++);
}

//����PWMռ�ձ�
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

	/* ����TIM3CLK Ϊ 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
  ----------------------------------------------------------------------- */
	
  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = TIME_PERIOD_CNT;      //����ʱ����0������2999����Ϊ3000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 8;	    //����Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = TIME_PERIOD_CNT / 2;	   	 //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��1
	
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//ʹ��TIM3Ԥװ��
	TIM_ARRPreloadConfig(TIM3, ENABLE);								//ʹ��TIM3���ؼĴ���ARR
	
	Beep_Amp(0);
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);           //ʹ�ܶ�ʱ��3	
}


