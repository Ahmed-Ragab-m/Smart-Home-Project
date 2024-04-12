#include "stand Types.h"
#include "utils.h"
#include "Memory_Map.h"
#include "UART.h"

void UART_Init(void)
{
	/* baud rate 9600 8MHZ clock*/
	UBRRL=51;
	/* frame 8 bit_data 1 stop no_parity */
	/* enable */
	set_bit(UCSRB,TXEN);
	set_bit(UCSRB,RXEN);
}

void UART_Send(u8 data)
{
	while(!read_bit(UCSRA,UDRE));
	UDR=data;
}

u8 UART_Receive(void)
{
	while(!read_bit(UCSRA,RXC));
	return UDR;
}

void UART_Send_Noblock(u8 data)
{
	UDR=data;
}

u8 UART_Receive_Noblock(void)
{
	return UDR;
}

/**********************************UART_Interrupt**************************************/

void UART_RX_InterruptEnable(void)
{
	set_bit(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	clear_bit(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	set_bit(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	clear_bit(UCSRB,TXCIE);
}

/**********************************Pointers******************************************/

static void (*UART_RX_Fptr) (void);
static void (*UART_TX_Fptr) (void);

/*********************************set call back functions***************************************/
void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
    UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
 {
	 UART_TX_Fptr = LocalFptr;
 }
 
/*********************************** ISR *************************************/
ISR(USART_RXC_vect)
 {
	 if (UART_RX_Fptr!=NULLPTR)
	 {
		 UART_RX_Fptr();
	 }
 }

ISR(USART_TXC_vect)
 {
	 if (UART_TX_Fptr!=NULLPTR)
	 {
		 UART_TX_Fptr();
	 }
 } 
