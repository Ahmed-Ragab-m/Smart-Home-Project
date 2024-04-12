#include "stand Types.h"
#include "utils.h"
#include "Memory_Map.h"
#include "Timers.h"

/*************************Pointer to functions to be assigned to ISR*********************************/

static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
static void (*Timer1_OCB_Fptr) (void)=NULLPTR;
static void (*Timer1_ICU_Fptr) (void)=NULLPTR;
/******************************************************************************************/
/*timer 0 functions*/
void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		clear_bit(TCCR0,WGM00);
		clear_bit(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		set_bit(TCCR0,WGM00);
		clear_bit(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		clear_bit(TCCR0,WGM00);
		set_bit(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		set_bit(TCCR0,WGM00);
		set_bit(TCCR0,WGM01);
		break;
	}
	TCCR0&=0XF8;//0b11111000
	TCCR0|=scaler;
}

void TIMER0_OC0Mode(OC0Mode_type mode)
{
	switch (mode)
	{
		case OC0_DISCONNECTED:
		clear_bit(TCCR0,COM00);
		clear_bit(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		set_bit(TCCR0,COM00);
		clear_bit(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		clear_bit(TCCR0,COM00);
		set_bit(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		set_bit(TCCR0,COM00);
		set_bit(TCCR0,COM01);
		break;
	}
}

void TIMER0_OV_InterruptEnable(void)
{
	set_bit(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	clear_bit(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	set_bit(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	clear_bit(TIMSK,OCIE0);
}

/*************************************************************************/
/*timer 1 functions*/
void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		clear_bit(TCCR1A,WGM10);
		clear_bit(TCCR1A,WGM11);
		clear_bit(TCCR1B,WGM12);
		clear_bit(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		clear_bit(TCCR1A,WGM10);
		clear_bit(TCCR1A,WGM11);
		set_bit(TCCR1B,WGM12);
		set_bit(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		clear_bit(TCCR1A,WGM10);
		clear_bit(TCCR1A,WGM11);
		set_bit(TCCR1B,WGM12);
		clear_bit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		clear_bit(TCCR1A,WGM10);
		set_bit(TCCR1A,WGM11);
		set_bit(TCCR1B,WGM12);
		set_bit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		set_bit(TCCR1A,WGM10);
		set_bit(TCCR1A,WGM11);
		set_bit(TCCR1B,WGM12);
		set_bit(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		clear_bit(TCCR1A,COM1A0);
		clear_bit(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		set_bit(TCCR1A,COM1A0);
		clear_bit(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		clear_bit(TCCR1A,COM1A0);
		set_bit(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		set_bit(TCCR1A,COM1A0);
		set_bit(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		clear_bit(TCCR1A,COM1B0);
		clear_bit(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		set_bit(TCCR1A,COM1B0);
		clear_bit(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		clear_bit(TCCR1A,COM1B0);
		set_bit(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		set_bit(TCCR1A,COM1B0);
		set_bit(TCCR1A,COM1B1);
		break;
	}
}
void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	set_bit(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	clear_bit(TCCR1B,ICES1);
}


/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	set_bit(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	clear_bit(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	set_bit(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	clear_bit(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	set_bit(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	clear_bit(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	set_bit(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	clear_bit(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULLPTR)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NULLPTR)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NULLPTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NULLPTR)
	{
		Timer1_ICU_Fptr();
	}
}