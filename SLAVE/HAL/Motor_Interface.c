#include "stand Types.h"
#include "DIO_Interface.h"
#include "Motor_Interface.h"
#include "Motor_Config.h"
#include "Timers.h"

/* ***********************DC MOTOR *******************************/

void MOTOR_ON_CW(MOTOR_NAME MOTOR)
{
	switch(MOTOR)
	{
		case MOTOR1:
		DIO_Write_pin(IN1,HIGH);
		//DIO_Write_pin(IN2,LOW);
		break;
		case MOTOR2:
		DIO_Write_pin(IN3,HIGH);
		DIO_Write_pin(IN4,LOW);
		break;
	}
}

void MOTOR_ON_CCW(MOTOR_NAME MOTOR)
{
		switch(MOTOR)
		{
			case MOTOR1:
			DIO_Write_pin(IN1,LOW);
			DIO_Write_pin(IN2,HIGH);
			break;
			case MOTOR2:
			DIO_Write_pin(IN3,LOW);
			DIO_Write_pin(IN4,HIGH);
			break;
		}
}

void MOTOR_STOP(MOTOR_NAME MOTOR)
{
	switch(MOTOR)
	{
		case MOTOR1:
		DIO_Write_pin(IN1,LOW);
		DIO_Write_pin(IN2,LOW);
		break;
		case MOTOR2:
		DIO_Write_pin(IN3,LOW);
		DIO_Write_pin(IN4,LOW);
		break;
	}
}

/* ------------------- Stepper Motor----------------*/



/*******************************Servo Motor**************************************/
void servo_motor(u8 position)
{
	OCR1A=(((u32)position*1000)/180)+1000;
}