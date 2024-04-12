#define Keypad_Interface
#include "stand Types.h"
#include "DIO_Interface.h"
#include "Keypad_Config.h"
#include "Keypad_Interface.h"


#define F_CPU  8000000
#include <util/delay.h>

void keypad_Init(void)
{
	for(u8 r=0;r<row;r++)
	{
		DIO_Write_pin(first_output+r,HIGH);
	}
	
}


u8 keypad_key(void)
{
	u8 r,c,key=no_key;
	for(r=0;r<row;r++)
	{
		DIO_Write_pin(first_output+r,LOW);
		for(c=0;c<col;c++)
		{
			if(!DIO_READ_pin(first_input+c))
			{
				key=keypad_arr[r][c];
				_delay_ms(1);
				while(!DIO_READ_pin(first_input+c));
				_delay_ms(1);
			}
		}
		DIO_Write_pin(first_output+r,HIGH);
	}
	return key;
	
}



