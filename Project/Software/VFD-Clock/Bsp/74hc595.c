#include "74hc595.h"

void HC595_Delay(u32 i)
{
  u8 j=0;
  for(j=0;j<0x1f;j++)
    while(i)i--;
}

/*
* Function:初始化595所用引脚
*/
void HC595_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(HC595_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = HC595_DATA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_SCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_RCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);
	
	// 改成PWM形式了
  // GPIO_InitStructure.GPIO_Pin = HC595_OE;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	// GPIO_Init(HC595_PORT, &GPIO_InitStructure);
  
	GPIO_ResetBits(HC595_PORT, HC595_DATA);
	GPIO_ResetBits(HC595_PORT, HC595_SCLK);
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
	// GPIO_ResetBits(HC595_PORT, HC595_OE);
}

/*
* Function:写入数据到移位寄存器里，先写低位。一个芯片正好一个字节
*/
void HC595_Input(uint8_t byte)
{
	uint8_t i, num;
	num = byte;
	for (i=0; i<8; i++)
	{
		GPIO_ResetBits(HC595_PORT, HC595_SCLK);
		if ((num&0x01)==0x01)
			GPIO_SetBits(HC595_PORT, HC595_DATA);
		else
			GPIO_ResetBits(HC595_PORT, HC595_DATA);
		GPIO_SetBits(HC595_PORT, HC595_SCLK);
		num = num>>1;
    HC595_Delay(1);
	}
}

/*
* Function:将数据从移位寄存器锁存到输出寄存器上
*/
void HC595_Latch(void)
{
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
	GPIO_SetBits(HC595_PORT, HC595_RCLK);
  HC595_Delay(1);
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
}

//功能：向595写入一串数据
//参数1：数组指针，每个字节为当前芯片的显示内容
//参数2：数组长度，等于级联的芯片数量减1
void HC595_WriteBytes(u8 *data,u8 num)
{
  u8 i;
  for(i=0;i<num;i++)
    HC595_Input(data[i]);
  HC595_Delay(1);
  HC595_Latch();
}

