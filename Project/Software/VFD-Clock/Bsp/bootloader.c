#include "bootloader.h"

// 清空初始化相关外设，根据需要自己处理
void DeInitDevice(void)
{
  // SysTick->CTRL=0x00;       //关闭计数器
  // SysTick->VAL =0X00;       //清空计数器	
}

void EnterBootLoader(void)
{
    //程序跳转不复位外设，建议对一些可能导致问题的外设进行反初始化DeInit，如SysTick。
		//看门狗一旦初始化不能被关闭，因此如果使用了看门狗，则在调用该函数前，必须先复位系统，并在初始化看门狗之前调用该函数。
		uint32_t ispJumpAddr;//ISP程序的跳转地址，既程序入口
		uint32_t ispSpValue;//IAP程序的SP初值，即栈指针
		void (*Jump_To_ISP)(void);//定义一个函数指针

    DeInitDevice();

	  if (((*(__IO uint32_t*)ISPAddress) & 0x2FFE0000 ) == 0x20000000)
    { 
			ispSpValue  = *(__IO uint32_t*)ISPAddress;
      ispJumpAddr = *(__IO uint32_t*)(ISPAddress+4);
      
      /* 初始化 Stack Pointer */
      __set_MSP(ispSpValue);
			
			/* Jump to isp */
			Jump_To_ISP = (void (*)(void))ispJumpAddr;
      Jump_To_ISP();
    }
}

