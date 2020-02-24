#ifndef __USART1_H
#define	__USART1_H

#include "bsp.h"

void USART1_Init(void);
void USART_SendString(USART_TypeDef* USARTx, u8* pBuffer, u16 len);
void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data);
#endif /* __USART1_H */
