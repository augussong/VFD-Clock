#include "ws2812b.h"

__IO u8 GammaLUT[256] = {0};//Gamma Look Up Table
__IO u8 WS2812_RGB[WS2812_NUM][3];
__IO u8 RcdMAX_RGB[WS2812_NUM][3];

__IO RGB_TypeDef RGB_Msg={255,128,64,RAINBOW,EFFECTS_ON};
//__IO RGB_TypeDef RGB_Rcd={255,128,64,1,255,0};//记录Msg
  
//建立gamma校正表，亮度线性化校正
void BuildGammaCorrectionTable(void)
{
    #define GammaON 1
    #if GammaON
        int i;
        float f;
        float Precompensation=0.7;
        for( i=0;i<256;i++)
        {
         f=i/256.0;//归一化
         f=(float)pow(f,Precompensation);
         GammaLUT[i]=(u8)(f*256.0+0.5);//反归一化
        }
    #else
        int i;
        for( i=0;i<256;i++)
        {
         GammaLUT[i] = i;
        }
    #endif
}

void WS2812_Send_0()   
{
	 WS2812_Set();
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();  
	 WS2812_Reset(); 
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
}

/*******************发送1码函数,高电平800ns,周期1.25us*************************/
void WS2812_Send_1()    
{
	 WS2812_Set();
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
	 WS2812_Reset(); 
   __NOP();__NOP();__NOP();__NOP();__NOP();
}

/***********************发送1个字节数据,高位先发*******************************/
void WS2812_Send_Data(unsigned char DATA)		
{
  u8 i=0;
  for(i=0;i<8;i++)
  {
    if(DATA&(0x80>>i))
      WS2812_Send_1();
    else
      WS2812_Send_0();
  }
}

/******************************发送1帧数据*************************************/
void WS2812_Send_Px(void)
{
	unsigned int row,line;

  // __disable_irq();
	for(line = 0; line < WS2812_NUM; line++ )
	{
    //强制转换为1维数组
    for(row = 0; row < 3; row++ ){
     WS2812_Send_Data( GammaLUT[ WS2812_RGB[line][row] ] * 0.2); 
//			 WS2812_Send_Data( WS2812_RGB[line][row] ); 
    }
	}
  // __enable_irq();
}

//填充管子颜色信息
//num:管子编号（从0开始）
//type:基色类型（G-0，R-1，B-2）
//value:颜色强度（0-255）
u8 TubeFillColor(u8 num,u8 type,u8 value)
{
    WS2812_RGB[num][type]=value;
    return value;
}

//填充管子最大颜色信息
//num:管子编号（0-3）
//type:基色类型（G-0，R-1，B-2）
//value:颜色强度（0-255）
void TubeMaxRGB(u8 num,u8 type,u8 value)
{
    RcdMAX_RGB[num][type]=value;
}

//管子呼吸效果
//num 管子编号
void TubeBreath(u8 num)
{
    static float step[WS2812_NUM]={0};
    #define STEPLENGTH 2*3.1415926/256

    WS2812_RGB[num][GREEN]=sin(step[num])*RcdMAX_RGB[num][GREEN];
    WS2812_RGB[num][RED]  =sin(step[num])*RcdMAX_RGB[num][RED];
    WS2812_RGB[num][BLUE] =sin(step[num])*RcdMAX_RGB[num][BLUE];
    step[num] += STEPLENGTH;

//    static u8 Rdown=0,Gdown=0,Bdown=0;
//    
//    if(Rdown)
//        WS2812_RGB[num][RED]--;
//    else
//        WS2812_RGB[num][RED]++;
//    if(Gdown)
//        WS2812_RGB[num][GREEN]--;
//    else
//        WS2812_RGB[num][GREEN]++;
//    if(Bdown)
//        WS2812_RGB[num][BLUE]--;
//    else
//        WS2812_RGB[num][BLUE]++;
//    
//    if(RcdMAX_RGB[num][RED]==0)WS2812_RGB[num][RED]=0;
//    if(RcdMAX_RGB[num][GREEN]==0)WS2812_RGB[num][GREEN]=0;
//    if(RcdMAX_RGB[num][BLUE]==0)WS2812_RGB[num][BLUE]=0;
//    
//    if(WS2812_RGB[num][RED]==RcdMAX_RGB[num][RED])Rdown=1;
//    else if(WS2812_RGB[num][RED]==0)Rdown=0;
//    if(WS2812_RGB[num][GREEN]==RcdMAX_RGB[num][GREEN])Gdown=1;
//    else if(WS2812_RGB[num][GREEN]==0)Gdown=0;
//    if(WS2812_RGB[num][BLUE]==RcdMAX_RGB[num][BLUE])Bdown=1;
//    else if(WS2812_RGB[num][BLUE]==0)Bdown=0;
}

//管子彩虹效果
//num 管子编号
u8 RainBowstate[WS2812_NUM]={0,1,2,3,4,5};
void TubeRainbow(u8 num)
{
    //各管子初始状态
    switch(RainBowstate[num])
    {
        case 0:
            WS2812_RGB[num][BLUE]++;
            if(WS2812_RGB[num][BLUE] >= MAX_LIGHT_LEVEL)RainBowstate[num]++;break;
        case 1:
            WS2812_RGB[num][RED]--;
            if(WS2812_RGB[num][RED] <= 0)RainBowstate[num]++;break;
        case 2:
            WS2812_RGB[num][GREEN]++;
            if(WS2812_RGB[num][GREEN] >= MAX_LIGHT_LEVEL)RainBowstate[num]++;break;
        case 3:
            WS2812_RGB[num][BLUE]--;
            if(WS2812_RGB[num][BLUE] <= 0)RainBowstate[num]++;break;
        case 4:
            WS2812_RGB[num][RED]++;
            if(WS2812_RGB[num][RED] >= MAX_LIGHT_LEVEL)RainBowstate[num]++;break;
        case 5:
            WS2812_RGB[num][GREEN]--;
            if(WS2812_RGB[num][GREEN] <= 0)RainBowstate[num]=0;break;
        default:break;
    }
}

//WS2812灯特效控制
//参数：RGB信息、亮度等级、是否呼吸，颜色模式
//RGB:0-255
//LEVEL:0-255
//mode:0-SingleColour;1-MultiColour
//真正使用的数据
float Ruse=0,Guse=0,Buse=0;
void WS2812_Breath(void)
{
    u8 i=0;
    static u8 MultiColorState=0;
    if(RGB_Msg.state==EFFECTS_ON)
    {
        if(RGB_Msg.mode==RAINBOW)
        {
            for(i=TUBE0;i<MAX_TUBE_NUM;i++)
                TubeRainbow(i);
        }
        else
        {
            if(RGB_Msg.mode==SINGLECOLOR)
            {
                for(i=TUBE0;i<MAX_TUBE_NUM;i++)
                    TubeBreath(i);
            }
            if(RGB_Msg.mode==MULTICOLOR)
            {
                switch(MultiColorState)
                {
                    case 0:
                        WS2812_RGB[TUBE0][RED]++;
                        WS2812_RGB[TUBE1][RED]++;
                        WS2812_RGB[TUBE2][RED]++;
                        WS2812_RGB[TUBE3][RED]++;
												WS2812_RGB[TUBE4][RED]++;
												WS2812_RGB[TUBE5][RED]++;
                        if(WS2812_RGB[TUBE0][RED] >= MAX_LIGHT_LEVEL)MultiColorState++;break;//首先是点亮
                    case 1:
                        WS2812_RGB[TUBE0][GREEN]++;
                        WS2812_RGB[TUBE1][GREEN]++;
                        WS2812_RGB[TUBE2][GREEN]++;
                        WS2812_RGB[TUBE3][GREEN]++;
												WS2812_RGB[TUBE4][GREEN]++;
												WS2812_RGB[TUBE5][GREEN]++;
                        if(WS2812_RGB[MAX_TUBE_NUM - 1][GREEN] >= MAX_LIGHT_LEVEL)MultiColorState++;break;//此时才是变色
                    case 2:
                        WS2812_RGB[TUBE0][RED]--;
                        WS2812_RGB[TUBE1][RED]--;
                        WS2812_RGB[TUBE2][RED]--;
                        WS2812_RGB[TUBE3][RED]--;
												WS2812_RGB[TUBE4][RED]--;
												WS2812_RGB[TUBE5][RED]--;
                        if(WS2812_RGB[MAX_TUBE_NUM - 1][RED]<=0)MultiColorState++;break;
                    case 3:
                        WS2812_RGB[TUBE0][BLUE]++;
                        WS2812_RGB[TUBE1][BLUE]++;
                        WS2812_RGB[TUBE2][BLUE]++;
                        WS2812_RGB[TUBE3][BLUE]++;
												WS2812_RGB[TUBE4][BLUE]++;
												WS2812_RGB[TUBE5][BLUE]++;
                        if(WS2812_RGB[MAX_TUBE_NUM - 1][BLUE] >= MAX_LIGHT_LEVEL)MultiColorState++;break;
                    case 4:
                        WS2812_RGB[TUBE0][GREEN]--;
                        WS2812_RGB[TUBE1][GREEN]--;
                        WS2812_RGB[TUBE2][GREEN]--;
                        WS2812_RGB[TUBE3][GREEN]--;
												WS2812_RGB[TUBE4][GREEN]--;
												WS2812_RGB[TUBE5][GREEN]--;
                        if(WS2812_RGB[MAX_TUBE_NUM - 1][GREEN] <= 0)MultiColorState++;break;
                    case 5:
                        WS2812_RGB[TUBE0][RED]++;
                        WS2812_RGB[TUBE1][RED]++;
                        WS2812_RGB[TUBE2][RED]++;
                        WS2812_RGB[TUBE3][RED]++;
										    WS2812_RGB[TUBE4][RED]++;
										    WS2812_RGB[TUBE5][RED]++;
                        if(WS2812_RGB[MAX_TUBE_NUM - 1][RED] >= MAX_LIGHT_LEVEL)MultiColorState++;break;
                    case 6:
                        WS2812_RGB[TUBE0][BLUE]--;
                        WS2812_RGB[TUBE1][BLUE]--;
                        WS2812_RGB[TUBE2][BLUE]--;
                        WS2812_RGB[TUBE3][BLUE]--;
										    WS2812_RGB[TUBE4][BLUE]--;
										    WS2812_RGB[TUBE5][BLUE]--;
                        if(WS2812_RGB[MAX_TUBE_NUM - 1][BLUE] <= 0)MultiColorState=1;break;//不应该从0开始
                    default:break;
                }
            }
        }
    }
    else if(RGB_Msg.state==EFFECTS_OFF)
    {
    }
    
    if(RGB_Msg.state==RGB_OFF)
    {
        memset((u8*)WS2812_RGB,0,sizeof(WS2812_RGB));
        MultiColorState=0;
    }
        
    WS2812_Send_Px();
}

//不管条件，强行写入RGB信息
void WS2812_Refresh(u8 R,u8 G,u8 B)
{
	u8 row=0,line=0;
	
	memset((u8*)WS2812_RGB,0,sizeof(WS2812_RGB));
	for(row=0;row<WS2812_NUM;row++)
    for(line=0;line<3;line++)
    {
      switch(line)
      {
        case 0:WS2812_RGB[row][line]=G;break;//R、G调换一下，因为好像定义不一样
        case 1:WS2812_RGB[row][line]=R;break;
        case 2:WS2812_RGB[row][line]=B;break;
      }
    }
       
  WS2812_Send_Px();
}


void WS2812_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_WS2812, ENABLE);

	GPIO_InitStructure.GPIO_Pin = Pin_WS2812;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_WS2812, &GPIO_InitStructure);

	BuildGammaCorrectionTable();
}


