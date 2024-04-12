#include "stand Types.h"
#include "utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"


#define F_CPU 8000000
#include "util/delay.h"


#if LCD_MODE==_4_BIT

static void LCD_Write_Inst(u8 inst)
{
	DIO_Write_pin(RS,LOW);
	DIO_Write_pin(D7,read_bit(inst,7));
	DIO_Write_pin(D6,read_bit(inst,6));
	DIO_Write_pin(D5,read_bit(inst,5));
	DIO_Write_pin(D4,read_bit(inst,4));
	DIO_Write_pin(EN,HIGH);
	_delay_ms(1);
	DIO_Write_pin(EN,LOW);
	_delay_ms(1);
	DIO_Write_pin(D7,read_bit(inst,3));
	DIO_Write_pin(D6,read_bit(inst,2));
	DIO_Write_pin(D5,read_bit(inst,1));
	DIO_Write_pin(D4,read_bit(inst,0));
	DIO_Write_pin(EN,HIGH);
	_delay_ms(1);
	DIO_Write_pin(EN,LOW);
	_delay_ms(1);
}
static void LCD_Write_Data(u8 data)
{
	DIO_Write_pin(RS,HIGH);
	DIO_Write_pin(D7,read_bit(data,7));
	DIO_Write_pin(D6,read_bit(data,6));
	DIO_Write_pin(D5,read_bit(data,5));
	DIO_Write_pin(D4,read_bit(data,4));
	DIO_Write_pin(EN,HIGH);
	_delay_ms(1);
	DIO_Write_pin(EN,LOW);
	_delay_ms(1);
	DIO_Write_pin(D7,read_bit(data,3));
	DIO_Write_pin(D6,read_bit(data,2));
	DIO_Write_pin(D5,read_bit(data,1));
	DIO_Write_pin(D4,read_bit(data,0));
	DIO_Write_pin(EN,HIGH);
	_delay_ms(1);
	DIO_Write_pin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_Write_Inst(0x02);  //  2  0  2   8
	LCD_Write_Inst(0x28);
	LCD_Write_Inst(0x0c);// 0X0E 0X0F  cursor
	LCD_Write_Inst(0x01);//clear lcd
	_delay_ms(1);
	LCD_Write_Inst(0x06);// DDRAM inc
}

#elif LCD_MODE==_8_BIT


static void LCD_Write_Inst(char inst)  // common instruction in LCD initialization
{
	DIO_Write_pin(RS,LOW);
	DIO_Write_Port(LCD_PORT,inst);
	DIO_Write_pin(EN,HIGH);
	_delay_ms(1);
	DIO_Write_pin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	LCD_Write_Inst(0x38); // function set
	LCD_Write_Inst(0x0C); // display on-off
	LCD_Write_Inst(0x01); // display clear
	_delay_ms(1);
	LCD_Write_Inst(0x06); // entry mode set

}

static void LCD_Write_Data(u8 data)
{
		DIO_Write_pin(RS,HIGH);
		DIO_Write_Port(LCD_PORT,data);
		DIO_Write_pin(EN,HIGH);
		_delay_ms(1);
		DIO_Write_pin(EN,LOW);
		_delay_ms(1);
}

# endif 


/*-----------------------------------------------------------------------------------------------------------------*/

void LCD_Write_char(u8 ch)
{
	LCD_Write_Data(ch);
}


void LCD_Write_String(u8*str)
{
	int i;
	for(i=0;str[i];i++)
	{
		LCD_Write_char(str[i]);
	}
}

void LCD_Write_Number(s16 num)
{
	u8 str[16];
	u16 i;
	s16 j;
	if(num==0)
	{
		LCD_Write_char('0');
		return;
	}
	if(num<0)
	{
		LCD_Write_char('-');
		num=num*-1;
	}
	for(i=0;num>0;i++)
	{
		str[i]=num%10+'0';
		num=num/10;
	}
	str[i]=0;
	for(j=i-1;j>=0;j--)
	{
		LCD_Write_char(str[j]);
	}

}

void LCD_Clear(void)
{
	LCD_Write_Inst(0x01); // display clear
	_delay_ms(1);
}

void LCD_Set_Cursor(u8 line,u8 cell)
{
	// line 0-1  cell 0-15
	if(line==0)
	{
		LCD_Write_Inst(0x80+cell);
	}
	else if(line==1)
	{
		LCD_Write_Inst(0x80+(0x40+cell));
	}
	
}

void LCD_Binary(u8 num)  // print number in binary
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		if((num>>i)&1)
		{
		    LCD_Write_char('1');
		}
		else 
		{
			LCD_Write_char('0');
		}
	}
}

void LCD_Hex_Num(int num)
{
	u8 HEX_Arr[]={'0','1','2','3','4','5','6','7',
	'8','9','A','B','C','D','E','F'};
	int h=num>>4;
	int l=num&0x0f;
	LCD_Write_char(HEX_Arr[h]);
	LCD_Write_char(HEX_Arr[l]);
    /*if(h<10)
	{
		LCD_Write_char(h+'0');
	}
	else
	{
		LCD_Write_char(h+'A'-10);
	}
	 if(l<10)
	 {
		 LCD_Write_char(l+'0');
	 }
	 else
	 {
		 LCD_Write_char(l+'A'-10);
	 } */
    
}

void LCD_string_snake(u8*str)
{
	u8 l,i;
	for(i=0;str[i];i++);
	l=i;
	for(i=1;i<l;i++)
	{
		LCD_Write_String(str+l-i);
		_delay_ms(300);
		LCD_Clear();
	}
	
	for(i=0;i<15;i++)
	{
		LCD_Set_Cursor(0,i);
		LCD_Write_String(str);
		_delay_ms(300);
		LCD_Clear();
	}
	
	for(i=1;i<l;i++)
	{
		LCD_Set_Cursor(1,0);
		LCD_Write_String(str+l-i);
		_delay_ms(300);
		LCD_Clear();
	}
	
	for(i=0;i<15;i++)
	{
		LCD_Set_Cursor(1,i);
		LCD_Write_String(str);
		_delay_ms(300);
		LCD_Clear();
	}
}

void lcd_write_shape(u8*shape_arr,u8 address)
{
	LCD_Write_Inst(0x40+address*8);
	for(u8 i=0;i<8;i++)
	{
		LCD_Write_char(shape_arr[i]);
	}
	LCD_Write_Inst(0x80);
	
}