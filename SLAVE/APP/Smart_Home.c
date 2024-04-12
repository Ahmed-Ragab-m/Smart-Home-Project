/*=======================================================================*/
/* Program: Smart Home Project                                           */
/* Description:  MC SLAVE Code                                           */
/*=======================================================================*/
#include "stand Types.h"      
#include "DIO_Interface.h"
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

#define F_CPU  8000000
#include <util/delay.h>
/*=======================================================================*/
/* =======================SLAVE Initialize===============================*/
void SLAVE_Init(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(Vref_AVCC,ADC_Prescaler64);
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	UART_Init();
}
/*=======================================================================*/
/* ---------------------GLOBAL VARIABLES---------------------------------*/
u8 ExitData=0;


int main()
{
	/*=======================================================================*/
	/*----------------------LOCAL VARIABLES----------------------------------*/
	u8 Access=0;
	u8 ActuatorData=0;
	u8 ModeData=0;
	u8 FanData=0;
	u8 LightData=0;
	u8 TVData=0;
	u8 PumpData=0;
	u16 Digital_Signal_Temp=0;
	u16 Digital_Signal_LDR=0;
	u16 Digital_Signal_Smoke=0;
	u16 Analog_Signal_Temp=0;
	u16 Analog_Signal_LDR=0;
	u16 Analog_Signal_Smoke=0;
	u16 Temp_Value=0;
	u16 Smoke_Value= 50 ;
	/*----------------------------------------------------------------------*/
	SLAVE_Init();
	//UART_Send('x');
	Access=UART_Receive();        // Receive Data From UART Master AVR To Open Access to My Home
	if(Access=='Z')
	{
		LCD_Clear();
		LCD_Set_Cursor(0,0);
		LCD_Write_String("Welcome To");
		LCD_Set_Cursor(1,0);
		LCD_Write_String("Your Home");
	}
	while(1)
	{
		ModeData=UART_Receive();
		/*-------------Automatic Mode--------------*/
		if(ModeData=='A')         // Automatic mode
		{
			LCD_Clear();
			LCD_Set_Cursor(0,0);
			LCD_Write_String("Automatic Mode");
			//sei();          // enable global interrupt
			while(1)
			{
				
			}
		}
		/*-------------Manual Mode--------------*/
		else if(ModeData=='M')    // Manual mode
		{
			LCD_Clear();
			LCD_Set_Cursor(0,0);
			LCD_Write_String("Manual Mode");
			_delay_ms(800);
			LCD_Clear();
			while(1)
			{
				ActuatorData=UART_Receive();
				/*-------------Control TV--------------*/
				if(ActuatorData=='T')          
				{
					TVData=UART_Receive();
					if(TVData=='1')
					{
						OpenTV();
					}
					else if(TVData=='0')
					{
						CloseTV();
					}
				}
			   /*-------------Control Light------------*/
				else if(ActuatorData=='L')    
				{
					LightData=UART_Receive();
					if(LightData=='1')
					{
						OpenLight();
					}
					else if(LightData=='0')
					{
						CloseLight();
					}
				}
				/*-------------Control Fan--------------*/
				else if(ActuatorData=='F')
				{
					FanData=UART_Receive();
					if(FanData=='1')
					{
						OpenFan();
						CloseWindow();
					}
					else if(FanData=='0')
					{
						CloseFan();
						OpenWindow();
					}
				}
				
				/*-------------Control Water Pump------------*/
				else if(ActuatorData=='P')
				{
					PumpData=UART_Receive();
					if(PumpData=='1')
					{
						OpenPump();
					}
					else if(PumpData=='0')
					{
						ClosePump();
					}
				}
				/*-------------Exit from manual mode------------*/
				else if(ActuatorData=='#')
				{
					ModeData=0;
					ActuatorData=0;
					CloseLight();
					CloseFan();
					CloseTV();
					ClosePump();
					break;
				}
			}
		}
		
	}
	
	else if(Access=='N')
	{
		LCD_Clear();
		LCD_Write_String("Security!!!!");
		LCD_Set_Cursor(1,0);
		LCD_Write_String("Restart System...");
	}
}

/*=======================================================================*/
void OpenLight(void)
{
	DIO_Write_pin(LED,HIGH);
	LCD_Set_Cursor(0,0);
	LCD_Write_String("Light ON ");
}
/*=======================================================================*/
void CloseLight(void)
{
	DIO_Write_pin(LED,LOW);
	LCD_Set_Cursor(0,0);
	LCD_Write_String("Light OFF");
}
/*=======================================================================*/
void OpenFan(void)
{
	DIO_Write_pin(FAN,HIGH);
	LCD_Set_Cursor(0,12);
	LCD_Write_String("FAN ON ");
}
/*=======================================================================*/
void CloseFan(void)
{
	DIO_Write_pin(FAN,LOW);
	LCD_Set_Cursor(0,12);
	LCD_Write_String("FAN OFF");
}
/*=======================================================================*/
void OpenWindow(void)
{
	servo_motor(180);
}
/*=======================================================================*/
void CloseWindow(void)
{
	servo_motor(0);
}
/*=======================================================================*/
void OpenTV(void)
{
	DIO_Write_pin(TV,HIGH);
	LCD_Set_Cursor(1,0);
	LCD_Write_String("TV ON ");
}
/*=======================================================================*/
void CloseTV(void)
{
	DIO_Write_pin(TV,LOW);
	LCD_Set_Cursor(1,0);
	LCD_Write_String("TV OFF");
}
/*=======================================================================*/
void OpenPump(void)
{
	DIO_Write_pin(PUMP,HIGH);
	DIO_Write_pin(Buzzer,HIGH);
	LCD_Set_Cursor(1,12);
	LCD_Write_String("Pump ON ");
}
/*=======================================================================*/
void ClosePump(void)
{
	DIO_Write_pin(PUMP,LOW);
	DIO_Write_pin(Buzzer,LOW);
	LCD_Set_Cursor(1,12);
	LCD_Write_String("Pump OFF");
}
/*=======================================================================*/


