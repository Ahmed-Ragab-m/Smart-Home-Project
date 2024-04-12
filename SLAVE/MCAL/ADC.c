#include "stand Types.h"
#include "Memory_Map.h"
#include "utils.h"
#include "ADC.h"



void ADC_Init(ADC_Vref vref,ADC_Prescaler Prescaler)
{
	// clock
	ADCSRA=ADCSRA&0xf8;
	ADCSRA=ADCSRA|Prescaler;
	// vref
	switch(vref)
	{
		case Vref_AREV:
		clear_bit(ADMUX,REFS0);
		clear_bit(ADMUX,REFS1);
		break;
		case Vref_AVCC:
		set_bit(ADMUX,REFS0);
		clear_bit(ADMUX,REFS1);
		break;
		case Vref_265:
		set_bit(ADMUX,REFS0);
		set_bit(ADMUX,REFS1);
		break;
	}
	set_bit(ADCSRA,ADEN);   //ADC enable
	clear_bit(ADMUX,ADLAR);  // way of store result in reg
	
}


u16 ADC_Read(ADC_Channel chanel)
{
	/* select channel*/
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|chanel;
	/* start conversion*/
	set_bit(ADCSRA,ADSC);
	/* wait until conversion end*/
	while(read_bit(ADCSRA,ADSC));  //busy wait or blocking loop
	/* read register */
	return ADC;

}

u8 busy_flag;

void ADC_start_conversion(ADC_Channel chanel)
{
	if(busy_flag==0)
	{
		/* select channel*/
		ADMUX=ADMUX&0xE0;
		ADMUX=ADMUX|chanel;
		/* start conversion*/
		set_bit(ADCSRA,ADSC);
		busy_flag=1;
	}
	
}

u16 ADC_get_read(void)
{
	/* wait until conversion end*/
	while(read_bit(ADCSRA,ADSC));  //busy wait or blocking loop
	/* read register */
	return ADC;
}

u16 ADC_get_read_periodic(u16 *data) // polling
{
	if(read_bit(ADCSRA,ADSC))
	{
		return 0;
	}
	else
	{
		*data=ADC;
		busy_flag=0;
		return 1;
	}
	
}

u16 ADC_GetRead_NoBlock(void)
{
	return ADC;
}


u16 ADC_Read_Volt(ADC_Channel chanel)
{
	u16 adc;
	adc=ADC_Read(chanel);
	u16 volt=(5*((u32)1000)*adc)/1024;  // 5=vref
	return volt;
}