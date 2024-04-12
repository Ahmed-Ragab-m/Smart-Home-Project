#include "stand Types.h"
#include "Memory_Map.h"
#include "utils.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"

void DIO_Initialize_PIN(DIO_PINS PIN,PIN_STATUS status)    // DIO PIN INTIALIZATION (pin,status)
{
	DIO_PORT PORT=PIN/8;
 	u8 PIN_NUM=PIN%8;
	switch(status)
	{
		case OUTPUT:
		switch(PORT)
		{
			case PA:
			set_bit(DDRA,PIN_NUM);
			clear_bit(PORTA,PIN_NUM);
			break;
			case PB:
			set_bit(DDRB,PIN_NUM);
			clear_bit(PORTB,PIN_NUM);
			break;
			case PC:
			set_bit(DDRC,PIN_NUM);
			clear_bit(PORTC,PIN_NUM);
			break;
			case PD:
			set_bit(DDRD,PIN_NUM);
			clear_bit(PORTD,PIN_NUM);
			break;
		}
		break;
		case INFREE:
		switch(PORT)
		{
			case PA:
			clear_bit(DDRA,PIN_NUM);
			clear_bit(PORTA,PIN_NUM);
			break;
			case PB:
			clear_bit(DDRB,PIN_NUM);
			clear_bit(PORTB,PIN_NUM);
			break;
			case PC:
			clear_bit(DDRC,PIN_NUM);
			clear_bit(PORTC,PIN_NUM);
			break;
			case PD:
			clear_bit(DDRD,PIN_NUM);
			clear_bit(PORTD,PIN_NUM);
			break;
		}
		break;
		case INPULL_UP:
		switch(PORT)
		{
			case PA:
			clear_bit(DDRA,PIN_NUM);
			set_bit(PORTA,PIN_NUM);
			break;
			case PB:
			clear_bit(DDRB,PIN_NUM);
			set_bit(PORTB,PIN_NUM);
			break;
			case PC:
			clear_bit(DDRC,PIN_NUM);
			set_bit(PORTC,PIN_NUM);
			break;
			case PD:
			clear_bit(DDRD,PIN_NUM);
			set_bit(PORTD,PIN_NUM);
			break;
		}
		break;
	}
}

void DIO_Write_pin(DIO_PINS PIN,PIN_VOLT volt)      // DIO PINS WRITE (HIGH --LOW)  (PIN,volt)
{
	DIO_PORT PORT=PIN/8;
	u8 PIN_NUM=PIN%8;
	
	
	if(volt==LOW)
		{
		    switch(PORT)
		  {
			case PA:
			clear_bit(PORTA,PIN_NUM);
			break;
			case PB:
			clear_bit(PORTB,PIN_NUM);
			break;
			case PC:
			clear_bit(PORTC,PIN_NUM);
			break;
			case PD:
			clear_bit(PORTD,PIN_NUM);
			break;
		}

		}
			
		else if(volt==HIGH)
		{
			switch(PORT)
			{
				case PA:
				set_bit(PORTA,PIN_NUM);
				break;
				case PB:
				set_bit(PORTB,PIN_NUM);
				break;
				case PC:
				set_bit(PORTC,PIN_NUM);
				break;
				case PD:
				set_bit(PORTD,PIN_NUM);
				break;
				
			}
		}
		
	
}



PIN_VOLT DIO_READ_pin(DIO_PINS PIN)     // READ PIN (PIN)
{
	DIO_PORT PORT=PIN/8;
	u8 PIN_NUM=PIN%8;
	PIN_VOLT volt=LOW;
	switch(PORT)
	{
		case PA:
		volt= read_bit(PINA,PIN_NUM);
		break;
		case PB:
		volt= read_bit(PINB,PIN_NUM);
		break;
		case PC:
		volt= read_bit(PINC,PIN_NUM);
		break;
		case PD:
		volt= read_bit(PIND,PIN_NUM);
		break;
	}
	return volt;
}


void DIO_Init(void)     // DIO INITIALIZATION ALL PINS
{
	DIO_PINS i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_Initialize_PIN(i,PINS_Arr[i]);
	}
	
	
}

void DIO_Write_Port(DIO_PORT PORT,char data)  // write on port
{
	switch(PORT)
	{
		case PA:
		PORTA=data;
		break;
		case PB:
		PORTB=data;
		break;
		case PC:
		PORTC=data;
		break;
		case PD:
		PORTD=data;
		break;
	}
	
}

void DIO_Toggle_PIN(DIO_PINS PIN)
{
	DIO_PORT PORT=PIN/8;
	u8 PIN_NUM=PIN%8;
	switch(PORT)
	{
		case PA:
		toggle_bit(PORTA,PIN_NUM);
		break;
		case PB:
		toggle_bit(PORTB,PIN_NUM);
		break;
		case PC:
		toggle_bit(PORTC,PIN_NUM);
		break;
		case PD:
		toggle_bit(PORTD,PIN_NUM);
		break;
	}
}