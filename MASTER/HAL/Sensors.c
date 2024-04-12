#include "stand Types.h"
#include "ADC.h"
#include "Sensors.h"
#include "Sensors_Config.h"


u16 Read_temp(void)
{
    u16 volt,temp;
    volt=ADC_Read_Volt(lm35_ch);
    temp=volt/10;      // temp*10  
    return temp;
}

u16 Read_pressure(void)
{
	u16 adc;
	adc=ADC_Read(MPX_415);
	u16 pressure;
	pressure = (((u32)(adc-55)*1000)/921)+150;
	return pressure/10;
	
}

/* ------- Temperature ------------*/

u16 temp_arr[10];
u16 temp_filtered;
u16 temp_unfiltered;
u8 flag;


void temp_init(void)
{
	//temp_filtered=Read_temp();
}

void temp_run(void)
{
	u8 static i=0;
	u16 temp,sum=0;
	temp_arr[i]=Read_temp();
	temp_unfiltered=temp_arr[i];
	i++;
	if(i==10)
	{
		i=0;
		flag=1;
	}
	if(flag==1)
	{
		for(u8 j=0;j<10;j++)
		{
			sum=sum+temp_arr[j];
		}
		
		temp_filtered= sum/10;
	}
	
}

u16 tempfiltered(void)
{
	return temp_filtered;
}

u16 tempunfiltered(void)
{
	return temp_unfiltered;
}

/***********************************ultrasonic sensor**************************************/


