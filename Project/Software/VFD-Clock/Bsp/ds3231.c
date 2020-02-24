#include "ds3231.h"

TIME_TypeDef SetTime,GetTime,Alarm;

//DS3231_INT开关
void DS3231_INT_EXTI_Switch(FunctionalState flag)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	GPIO_EXTILineConfig(DS3231_INT_EXTI_PORT_SOURCE, DS3231_INT_EXTI_PIN_SOURCE); 
	
	EXTI_InitStructure.EXTI_Line = DS3231_INT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
	
	EXTI_InitStructure.EXTI_LineCmd = flag;
	
	EXTI_Init(&EXTI_InitStructure); 
}

/*设置EXTI功能去检测INT脚*/
void DS3231_INT_EXTI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(DS3231_INT_RCC | RCC_APB2Periph_AFIO,ENABLE);
												
	/* config the NVIC */
//	NVIC_Configuration();//其他地方处理了

	/* EXTI line gpio config*/	
  GPIO_InitStructure.GPIO_Pin = DS3231_INT_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
  GPIO_Init(DS3231_INT_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  DS3231_INT_EXTI_Switch(DISABLE);
}


void DS3231_GPIO_Init(void)
{
	//初始化IIC引脚并检查IIC设备
	i2c_CheckDevice(DS3231_ADDRESS);
}

//设置秒中断，输出到INT脚上
void DS3231_SetSecondAlarm(void)
{
	u8 ctrldata=0;
	u8 data=0x80;//为什么是0x80见手册Table2
	
	//使能Alarm1中断
	ctrldata=0x01;
	IIC_WriteBytes(&ctrldata,DS3231_ControlReg,1,DS3231_ADDRESS);
	
	//配置Alarm1模式
//	if(IIC_WriteBytes(&data,DS3231_A1SecReg,4,DS3231_ADDRESS)==1) return SUCCESS;
//	else return ERROR;
	IIC_WriteBytes(&data,DS3231_A1SecReg,1,DS3231_ADDRESS);//为啥不能连续写？
	IIC_WriteBytes(&data,DS3231_A1MinReg,1,DS3231_ADDRESS);
	IIC_WriteBytes(&data,DS3231_A1HourReg,1,DS3231_ADDRESS);
	IIC_WriteBytes(&data,DS3231_A1WeekReg,1,DS3231_ADDRESS);
}

/*配置DS3231*/
void DS3231_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); 
  
  DS3231_GPIO_Init();//config the iic
  DS3231_INT_EXTI_Init();//config the Int pin
  DS3231_SetSecondAlarm();//set second alarm
}

void DS3231_WriteTime(TIME_TypeDef* time)
{
	u8 setTime[7]={0};
  u8 i=0;
	setTime[0]=time->sec;
	setTime[1]=time->min;
	setTime[2]=time->hour;
	setTime[3]=time->week;
	setTime[4]=time->date;
	setTime[5]=time->month;
	setTime[6]=time->year;
//	if(IIC_WriteBytes(&setTime[0],DS3231_SecReg,7,DS3231_ADDRESS)==1) printf("Write OK\r\n");
//	else printf("Write Failed!\r\n");
  while(i<5)
  {
    i++;
    if(IIC_WriteBytes(&setTime[0],DS3231_SecReg,7,DS3231_ADDRESS)==1) 
    {
      printf("Write OK\r\n");
      break;
    }
	  else printf("Write Failed!\r\n");
  }
}

void DS3231_ReadTime(TIME_TypeDef* time)
{
	  u8 getTime[7]={0};
		if(IIC_ReadBytes(&getTime[0],DS3231_SecReg,7,DS3231_ADDRESS)==1) 
		{
//			printf("time:%x-%x-%x %x:%x:%x\r\n",getTime[6],getTime[5],getTime[4],getTime[2],getTime[1],getTime[0]);
			time->sec =getTime[0];
			time->min =getTime[1];
			time->hour =getTime[2];
			time->week =getTime[3];
			time->date =getTime[4];
			time->month =getTime[5];
			time->year =getTime[6];
		}
    #ifdef DEBUG
		else 
      printf("Read failed!\r\n");
    #endif
}

//读取指定寄存器数据
u8 DS3231_ReadReg(u8 Reg)
{
	u8 data;
	IIC_ReadBytes(&data,Reg,1,DS3231_ADDRESS);
	return data;
}

//向指定寄存器写入数据
u8 DS3231_WriteReg(u8 Reg,u8 data)
{
	if(IIC_WriteBytes(&data,Reg,1,DS3231_ADDRESS)==1) return SUCCESS;
	else return ERROR;
}

//读取所有寄存器
void DS3231_ReadAll(void)
{
	  u8 array[19]={0},i=0;
		if(IIC_ReadBytes(&array[0],DS3231_SecReg,19,DS3231_ADDRESS)==1) 
		{
			for(i=0;i<19;i++)
			printf("Reg0x%x:0x%x\r\n",i,array[i]);
		}
		else printf("Read failed!\r\n");
}

/************************************end of file 2014-08-08*********************************/
