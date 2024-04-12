
#ifndef ADC_H_
#define ADC_H_


typedef enum{
	Vref_AREV,
	Vref_AVCC,
	Vref_265
}ADC_Vref;

typedef enum{
	CH0,
	CH1,
	CH2,
	CH3,
	CH4,
	CH5,
	CH6,
	CH7
}ADC_Channel;

typedef enum{
	ADC_Prescaler2=1,
	ADC_Prescaler4,
	ADC_Prescaler8,
	ADC_Prescaler16,
	ADC_Prescaler32,
	ADC_Prescaler64,
	ADC_Prescaler128,
}ADC_Prescaler;

void ADC_Init(ADC_Vref vref,ADC_Prescaler Prescaler);
u16 ADC_Read(ADC_Channel chanel);
u16 ADC_Read_Volt(ADC_Channel chanel);
void ADC_start_conversion(ADC_Channel chanel);
u16 ADC_get_read(void);
u16 ADC_get_read_periodic(u16 *data);
u16 ADC_GetRead_NoBlock(void);



#endif /* ADC_H_ */