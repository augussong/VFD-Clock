#include "sht2x.h"

SHT2x_data SHT20;

void SHT2X_Delay_ms(u16 cnt)
{
//  OS_ERR err;
//  OSTimeDlyHMSM(0, 0, 0, cnt, OS_OPT_TIME_HMSM_STRICT, &err);
  int i = 0, j = 0;
  for(i = 0; i < cnt; i++)
    for(j = 0; j < 0xfff; j++){}
}

u8 SHT2x_Init(void)
{
  u8 status;
  i2c_CheckDevice(SHT2x_ADR_W);

  if(!i2c_CheckDevice(SHT2x_ADR_W))
    status = SHT2x_SoftReset();
  else
    status = 1; //δ��⵽�豸��
    return status;
}

u8 SHT2x_SoftReset(void) //SHT20�����λ
{
    u8 err=0;
    i2c_Start();
    i2c_SendByte(0x80);
    err = i2c_WaitAck();
    i2c_SendByte(0xFE);
    err = i2c_WaitAck();
    i2c_Stop();
    return err;
}
float SHT2x_GetTempPoll(void)
{
    float TEMP;
    u8 ack, tmp1, tmp2;
    u16 ST;
    u16 i=0;
    i2c_Start();				//����IIC��ʼ�ź�
    i2c_SendByte(SHT2x_ADR_W);			//IIC����һ���ֽ� 
    ack = i2c_WaitAck();	
    i2c_SendByte(TRIG_TEMP_MEASUREMENT_POLL);
    ack = i2c_WaitAck();

    do{
        SHT2X_Delay_ms(1);	//��������1ms���ӳ�               
        i2c_Start();				//����IIC��ʼ�ź�
        i2c_SendByte(SHT2x_ADR_R);	
        i++;
        ack = i2c_WaitAck();
        if(i==100)break;
    } while(ack!=0);
    tmp1 = i2c_ReadByte();
    tmp2 = i2c_ReadByte();
    i2c_ReadByte();
    i2c_Stop();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
	
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;

    return (TEMP);	  
}

float SHT2x_GetHumiPoll(void)
{
    float HUMI;
    u8 ack, tmp1, tmp2;
    u16 SRH;
    u16 i=0;

    i2c_Start();				//����IIC��ʼ�ź�
    i2c_SendByte(SHT2x_ADR_W);			//IIC����һ���ֽ� 
    ack = i2c_WaitAck();	
    i2c_SendByte(TRIG_HUMI_MEASUREMENT_POLL);
    ack = i2c_WaitAck();    
    do {
        SHT2X_Delay_ms(1);  //��������1ms���ӳ�              
        i2c_Start();				//����IIC��ʼ�ź�
        i2c_SendByte(SHT2x_ADR_R);	
        i++;
        ack = i2c_WaitAck();
        if(i==100)break;
    } while(ack!=0);
    
    tmp1 = i2c_ReadByte();

    tmp2 = i2c_ReadByte();
    i2c_ReadByte();
    i2c_Stop();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    return (HUMI);
}


