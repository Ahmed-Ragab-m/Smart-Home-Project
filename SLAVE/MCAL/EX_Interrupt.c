#include "stand Types.h"
#include "utils.h"
#include "Memory_Map.h"
#include "EX_Interrupt.h"




/************************************Enable/Disable functions***********************************/
void EXI_Enable(EX_Interrupt interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
		set_bit(GICR,INT0);
		break;
		case EX_INT1:
		set_bit(GICR,INT1);
		break;
		case EX_INT2:
		set_bit(GICR,INT2);
		break;
	}
}

void EXI_Disable(EX_Interrupt interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
		clear_bit(GICR,INT0);
		break;
		case EX_INT1:
		clear_bit(GICR,INT1);
		break;
		case EX_INT2:
		clear_bit(GICR,INT2);
		break;
	}
}

void EXI_Init(void)
{
	EXI_TriggerEdge(EX_INT0,falling_edge);
	EXI_TriggerEdge(EX_INT1,falling_edge);
	EXI_TriggerEdge(EX_INT2,falling_edge);
}

/************************************Control function*****************************/

void EXI_TriggerEdge(EX_Interrupt interrupt,Trigger_edge edge)
{
	switch(interrupt)
	{
		case EX_INT0:
		switch(edge)
		{
			case low_level:
			clear_bit(MCUCR,ISC00);
			clear_bit(MCUCR,ISC01);
			break;
			case logical_change:
			set_bit(MCUCR,ISC00);
			clear_bit(MCUCR,ISC01);
			break;
			case falling_edge:
			clear_bit(MCUCR,ISC00);
			set_bit(MCUCR,ISC01);
			break;
			case rising_edge:
			set_bit(MCUCR,ISC00);
			set_bit(MCUCR,ISC01);
			break;
		}
		break;
		case EX_INT1:
		switch(edge)
		{
			case low_level:
			clear_bit(MCUCR,ISC10);
			clear_bit(MCUCR,ISC11);
			break;
			case logical_change:
			set_bit(MCUCR,ISC10);
			clear_bit(MCUCR,ISC11);
			break;
			case falling_edge:
			clear_bit(MCUCR,ISC10);
			set_bit(MCUCR,ISC11);
			break;
			case rising_edge:
			set_bit(MCUCR,ISC10);
			set_bit(MCUCR,ISC11);
			break;
		}
		break;
		case EX_INT2:
		switch(edge)
		{
			case falling_edge:
			clear_bit(MCUCSR,ISC2);
			break;
			case rising_edge:
			set_bit(MCUCSR,ISC2);
			break;
			default:
			clear_bit(MCUCSR,ISC2);
		}
		break;
	}
}

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*INT0_Fptr) (void)=0;
static void (*INT1_Fptr) (void)=0;
static void (*INT2_Fptr) (void)=0;


/************************************Call back functions*********************************************/
void EXI_SetCallBack(EX_Interrupt Interrupt,void(*LocalPtr)(void))
{
	switch(Interrupt){
		case EX_INT0:
		INT0_Fptr=LocalPtr;
		break;
		case EX_INT1:
		INT1_Fptr=LocalPtr;
		break;
		case EX_INT2:
		INT2_Fptr=LocalPtr;
		break;
		
	}
}

/*******************************ISR********************************/

ISR(INT0_vect)
{
	
	
	if (INT0_Fptr!=0)
	{
		INT0_Fptr();
	}
	
	
}
ISR(INT1_vect,ISR_NOBLOCK)
{

	if (INT1_Fptr!=0)
	{
		INT1_Fptr();
	}
}
ISR(INT2_vect)
{
	if (INT2_Fptr!=0)
	{
		INT2_Fptr();
	}
	
}






