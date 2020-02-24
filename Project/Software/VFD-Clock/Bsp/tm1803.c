#include "TM1803.h"


//行表示灯的数量，列表示RGB数据
u8 TM1803_RGB[TM1803_NUM][3]={0};

void TM1803_Init(void)
{
//		GPIO_InitTypeDef GPIO_InitStructure;

//		RCC_APB2PeriphClockCmd(RCC_TM1803, ENABLE);
//		
//		GPIO_InitStructure.GPIO_Pin = Pin_TM1803;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(PORT_TM1803, &GPIO_InitStructure);

		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TM1803_Send_0()   
{
	 TM1803_Set;
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();  
	 TM1803_Reset; 
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
}

/*******************发送1码函数,高电平800ns,周期1.25us*************************/
void TM1803_Send_1()    
{
	 TM1803_Set;
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
	 TM1803_Reset; 
   __NOP();__NOP();__NOP();__NOP();__NOP();
}

/***********************发送1个字节数据,高位先发*******************************/
void TM1803_Send_Data(unsigned char DATA)		
{
  u8 i=0;
  for(i=0;i<8;i++)
  {
    if(DATA&(0x80>>i))
      TM1803_Send_1();
    else
      TM1803_Send_0();
  }
}

/******************************发送1帧数据*************************************/
void TM1803_Send_Px(void)
{
	unsigned int row,line;

  // __disable_irq();
	for(line=0;line<TM1803_NUM;line++)
	{
    for(row=0;row<3;row++)
      TM1803_Send_Data(TM1803_RGB[line][row]); 
	}
  // __enable_irq();
}


void TM1803_Flash_Test(void)
{
  static u8 state=0;
  u8 row=0,line=0;
  for(row=0;row<TM1803_NUM;row++)
    for(line=0;line<3;line++)
    {
      if(state)
        TM1803_RGB[row][line]=0xff;
      else
        TM1803_RGB[row][line]=0;
    }
    
  state=~state;
    
//    if(state)
//    {
//      TM1803_RGB[0][0]=255; TM1803_RGB[0][1]=255; TM1803_RGB[0][2]=255; 
//      TM1803_RGB[1][0]=0; TM1803_RGB[1][1]=0; TM1803_RGB[1][2]=0;
//      TM1803_RGB[2][0]=255; TM1803_RGB[2][1]=255; TM1803_RGB[2][2]=255;
//      TM1803_RGB[3][0]=0; TM1803_RGB[3][1]=0; TM1803_RGB[3][2]=0; 
//    }
//    else
//    {
//      TM1803_RGB[0][0]=0; TM1803_RGB[0][1]=0; TM1803_RGB[0][2]=0; 
//      TM1803_RGB[1][0]=255; TM1803_RGB[1][1]=255; TM1803_RGB[1][2]=255;
//      TM1803_RGB[2][0]=0; TM1803_RGB[2][1]=0; TM1803_RGB[2][2]=0;
//      TM1803_RGB[3][0]=255; TM1803_RGB[3][1]=255; TM1803_RGB[3][2]=255;
//    }  
  TM1803_Send_Px();
}
