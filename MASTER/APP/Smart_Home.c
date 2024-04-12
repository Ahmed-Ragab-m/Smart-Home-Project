/*=======================================================================*/
/* Program: Smart Home Project                                           */
/* Description:  MC MASTER Code                                          */
/*=======================================================================*/
#include "stand Types.h"      
#include "DIO_Interface.h"
#include "Keypad_Interface.h"
#include "LCD_Interface.h"
#include "ADC.h"
#include "EX_Interrupt.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "UART_Services.h"
#include "UART.h"
#include "Sensors.h"
#include "Motor_Interface.h"
#include "Smart_Home.h"
#include "I2C.h"
#include "EEPROM.h"


u8 ModeKey=0;
u8 User=0;
u8 EEPROM_Password=0;

int main()
{
	DIO_Init();
	LCD_Init();
	keypad_Init();
	ADC_Init(Vref_AVCC,ADC_Prescaler64);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	
	UART_Init();
	I2C_MasterInit(0);
	EEPROM_WriteData(1,123);		// Ahmed Password
	EEPROM_WriteData(2,147);		// Mohamed Password
	StartSmartHome();
	SelectUserName();
	u16 password=0;
	while(1)
	{
		for(int i=0;i<3;i++)
		{
			password=GetPassword();
			if(password==EEPROM_Password)
			{
				UART_Send('Z');
				LCD_Clear();
				LCD_Set_Cursor(0,4);
				LCD_Write_String("WELLCOME...");
				OpenDoor();
				LCD_Set_Cursor(1,4);
				LCD_Write_String("Door Opend");
				_delay_ms(1000);
				LCD_Clear();
				LCD_Set_Cursor(0,4);
				LCD_Write_String("Select Mode");
				LCD_Set_Cursor(1,0);
				LCD_Write_String("1-Manual");
				LCD_Set_Cursor(1,10);
				LCD_Write_String("2-Automatic");
				while(1)
				{
					ModeKey=keypad_key();
					if(ModeKey!=no_key)
					{
						if(ModeKey=='1')
						{
							MaualMode();
						}
						else if(ModeKey=='2')
						{
							AutomaticMode();
						}
					}
				}
				
				
			}
		}
		
	}
}
*/

/*=======================================================================*/
void StartSmartHome(void)
{
	LCD_Set_Cursor(0,4);
	LCD_Write_String("WELCOME TO");
	LCD_Set_Cursor(1,4);
	LCD_Write_String("SMART HOME");
	_delay_ms(1000);
}

/*=======================================================================*/
void SelectUserName(void)
{
	u8 UserKey=0;
	LCD_Clear();
	LCD_Set_Cursor(0,2);
	LCD_Write_String("Select User Name");
	LCD_Set_Cursor(1,0);
	LCD_Write_String("1-Ahmed");
	LCD_Set_Cursor(1,10);
	LCD_Write_String("2-Mohamed");
	while(1)
	{
		UserKey=keypad_key();
		if(UserKey!=no_key)
		{
			if(UserKey=='1')
			{
				User=1;
				EEPROM_Password=EEPROM_ReadData(1);   
			}
			if(UserKey=='2')
			{
				User=2;
				EEPROM_Password=EEPROM_ReadData(2);
			}
			if(EEPROM_Password!='0')
			{
				break;
			}
	
		}
		
	}
	
	
}
/*=======================================================================*/
u16 GetPassword(void)
{
	u8 Password=0;
	u8 pressedKey=0;
	u8 TempPass=0;
	LCD_Clear();
	LCD_Set_Cursor(0,3);
	LCD_Write_String("Enter Password");
	LCD_Set_Cursor(1,0);
	while(1)
	{
		pressedKey=keypad_key();
		if(pressedKey!=no_key)
		{
			if(pressedKey>='0' && pressedKey<='9')
			{
				LCD_Write_char('*');
				TempPass=TempPass*10 + (pressedKey-'0');
			}
			if(pressedKey=='=')
			{
				Password=TempPass;
				break;
			}
		}
	}
	return Password;
	
}
/*=======================================================================*/
void MaualMode(void)  /* to run manual mode send M and to exit send #*/
{
	u8 ActuatorKey=0;
	UART_Send('M');
	LCD_Clear();
	while(1)
	{
		LCD_Set_Cursor(0,0);
		LCD_Write_String("1-Light   2-Fan");
		LCD_Set_Cursor(1,0);
		LCD_Write_String("3-TV      4-Pump");
		ActuatorKey=keypad_key();
		if(ActuatorKey!=no_key)
		{
			if(ActuatorKey=='1')
			{
				ControlLight();
			}
			else if(ActuatorKey=='2')
			{
				ControlFan();
			}
			else if(ActuatorKey=='3')
			{
				ControlTV();
			}
			else if(ActuatorKey=='4')
			{
				ControlPump();
			}
			else if(ActuatorKey=='#')
			{
				UART_Send('#');
				ModeKey=0;
				break;
			}
		}
	}
}
/*=======================================================================*/
void AutomaticMode(void) /* to run Automatic mode send A to exit press #*/
{
	u8 ExitAutoKey=0;
	UART_Send('A');
	LCD_Set_Cursor(0,0);
	LCD_Write_String("Automatic Mode");
	while(1)
	{
		ExitAutoKey=keypad_key();
		if(ExitAutoKey!=no_key)
		{
			if(ExitAutoKey=='#')
			{
				UART_Send('#');
				LCD_Clear();
				ModeKey=0;
				break;
			}
		}
	}
}
/*=======================================================================*/
void ControlLight(void)   /* to control light press L then select 1 to ON or 0 to OFF*/
{
	u8 LightKey=0;
	UART_Send('L');
	LCD_Clear();
	LCD_Set_Cursor(0,0);
	LCD_Write_String("1-Light: ON");
	LCD_Set_Cursor(1,0);
	LCD_Write_String("0-Light: OFF");
	while(1)
	{
		LightKey=keypad_key();
		if(LightKey!=no_key)
		{
			if(LightKey=='1')
			{
				UART_Send('1');
				LCD_Clear();
				break;
			}
			else if(LightKey=='0')
			{
				UART_Send('0');
				LCD_Clear();
				break;
			}
		}
	}
	
}
/*=======================================================================*/
void ControlFan(void)   /* to control FAN press L then select 1 to ON or 0 to OFF*/
{
	u8 FanKey=0;
	UART_Send('F');
	LCD_Clear();
	LCD_Set_Cursor(0,0);
	LCD_Write_String("1-FAN: ON");
	LCD_Set_Cursor(1,0);
	LCD_Write_String("0-FAN: OFF");
	while(1)
	{
		FanKey=keypad_key();
		if(FanKey!=no_key)
		{
			if(FanKey=='1')
			{
				UART_Send('1');
				LCD_Clear();
				break;
			}
			else if(FanKey=='0')
			{
				UART_Send('0');
				LCD_Clear();
				break;
			}
			
		}
	}
}
/*=======================================================================*/
void ControlTV(void)      /* to control TV press L then select 1 to ON or 0 to OFF*/
{
	u8 TVKey=0;
	UART_Send('T');
	LCD_Clear();
	LCD_Set_Cursor(0,0);
	LCD_Write_String("1-TV: ON");
	LCD_Set_Cursor(1,0);
	LCD_Write_String("2-TV: OFF");
	while(1)
	{
		TVKey=keypad_key();
		if(TVKey!=no_key)
		{
			if(TVKey=='1')
			{
				UART_Send('1');
				LCD_Clear();
				break;
			}
		}
		else if(TVKey=='0')
		{
			UART_Send('0');
			LCD_Clear();
			break;
		}
	}
}
/*=======================================================================*/
void ControlPump(void)      /* to control Pump press L then select 1 to ON or 0 to OFF*/
{
	u8 PumpKey=0;
	UART_Send('P');
	LCD_Clear();
	LCD_Set_Cursor(0,0);
	LCD_Write_String("1-Pump: ON");
	LCD_Set_Cursor(1,0);
	LCD_Write_String("0-Pump OFF");
	while(1)
	{
		PumpKey=keypad_key();
		if(PumpKey!=no_key)
		{
			if(PumpKey=='1')
			{
				UART_Send('1');
				LCD_Clear();
				break;
			}
			else if(PumpKey=='0')
			{
				UART_Send('0');
				LCD_Clear();
				break;
			}
		}
	}
}
/*=======================================================================*/
void OpenDoor(void)
{
	ICR1=19999;
	servo_motor(90);
}
/*=======================================================================*/
void CloseDoor(void)
{
	servo_motor(0);
}
/*=======================================================================*/


