#include "app.h"

extern	OS_TCB	StartUp_TCB;					

static  OS_TCB	LED1_TCB;		   				
__align(8) static	CPU_STK	LED1_Stk[TASK_LED1_STK_SIZE];	   

static  OS_TCB	LED2_TCB;		   				
__align(8) static	CPU_STK	LED2_Stk[TASK_LED2_STK_SIZE];	   	

/* 
 * ��������Task_Start
 * ����  : ��������
 *			   ���ȼ�Ϊ3��
 *		     ����LED1��LED2��LED3������
 * ����  ����
 * ���  : ��
 */
void Task_Start(void *p_arg)
{
	OS_ERR err;
  (void)p_arg;	

	//��������LED1	
	OSTaskCreate((OS_TCB     *)&LED1_TCB,					            // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED1",						            // ��������
               (OS_TASK_PTR )Task_LED1,					            // �������ָ��
               (void       *)0,							                // ���ݸ�����Ĳ���parg
               (OS_PRIO     )TASK_LED1_PRIO,				        // �������ȼ�
               (CPU_STK    *)&LED1_Stk[0],				          // �����ջ����ַ
               (CPU_STK_SIZE)TASK_LED1_STK_SIZE/10,		      // ��ջʣ�ྯ����
               (CPU_STK_SIZE)TASK_LED1_STK_SIZE,			      // ��ջ��С
               (OS_MSG_QTY  )0,							                // �ɽ��յ������Ϣ������
               (OS_TICK     )0,							                // ʱ��Ƭ��תʱ��
               (void       *)0,							                // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	        // ����ѡ��
               (OS_ERR     *)&err);						              // ����ֵ

	//��������LED2	
	OSTaskCreate((OS_TCB     *)&LED2_TCB,					     
               (CPU_CHAR   *)"LED2",						
               (OS_TASK_PTR )Task_LED2,					
               (void       *)0,							
               (OS_PRIO     )TASK_LED2_PRIO,				
               (CPU_STK    *)&LED2_Stk[0],				
               (CPU_STK_SIZE)TASK_LED2_STK_SIZE/10,		
               (CPU_STK_SIZE)TASK_LED2_STK_SIZE,			
               (OS_MSG_QTY  )0,							
               (OS_TICK     )0,							
               (void       *)0,							
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	 
               (OS_ERR     *)&err);					
  
  //welcome
  displayALL();
  OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
  displayHello();
  OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);

  DS3231_ReadTime(&GetTime);
  SHT20.TEMP_POLL = SHT2x_GetTempPoll();
  SHT20.HUMI_POLL = SHT2x_GetHumiPoll();
  displayTemp();
  OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
  displayHumi();
  OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
  DS3231_INT_EXTI_Switch(ENABLE);
               
  //����ɾ���Լ�	
	OSTaskDel(&StartUp_TCB,&err); 
}


/* 
 * ��������
 * ����  : 
 * ����  ����
 * ���  : ��
 */
void Task_LED1(void *p_arg)
{
  OS_ERR err;
  (void)p_arg;                	
  while (1)
  {
//    printf("Time:%02x-%02x-%02x %02x:%02x:%02x Temp:%05.2f Humi:%05.2f \n",
//          GetTime.year,GetTime.month,GetTime.date,
//          GetTime.hour,GetTime.min,GetTime.sec, SHT20.TEMP_POLL, SHT20.HUMI_POLL);
//    LED1( ON );
//    OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
//    LED1( OFF);
    OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
  }
}

/* 
 * ��������Task_LED2
 * ����  : 	LED����2��
 *         ���ȼ�Ϊ5��
 *         ��200ms�ļ���������ر�LED2
 * ����  ����
 * ���  : ��
 */
void Task_LED2(void *p_arg)
{
  OS_ERR err;
  (void)p_arg;

  while (1)
  {
    LED2( ON );
    OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
    LED2( OFF);
    OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
//		__disable_irq();
//    WS2812_Breath();
//		__enable_irq();
//		Beep_Amp(10);

//    OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
//    USART_SendString(USART2, "AT+GMR\r\n", 9);
  }
}

/* -------------------------------------end of file------------------------------------ */
