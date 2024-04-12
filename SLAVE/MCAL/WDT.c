#include "stand Types.h"
#include "utils.h"
#include "Memory_Map.h"
#include "WDT.h"

void WDT_Set(TimeOut time)
{
	u8 wdt_value=0x08;//WDE SET & WDTOE CLEARED 0B00001000
	wdt_value|=time;//0B00001011
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	WDTCR=wdt_value;
}


void WDT_Stop(void)
{
	WDTCR=(1<<WDTOE)|(1<<WDE);
	WDTCR=0;
}