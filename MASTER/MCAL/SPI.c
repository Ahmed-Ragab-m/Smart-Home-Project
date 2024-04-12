#include "stand Types.h"
#include "utils.h"
#include "Memory_Map.h"
#include "SPI.h"

void SPI_Int(SPI_Mode mode)
{
	if(mode==MASTER)
	{
		// clock 2MHz
		set_bit(SPCR,MSTR);
	}
	else
	{
		clear_bit(SPCR,MSTR);
	}
	// SPI Enable
	set_bit(SPCR,SPE);
	
}

u8 SPI_Send_Recieve(u8 data)
{
	SPDR=data;
	while(!read_bit(SPSR,SPIF));
	return SPDR;
}

u8 SPI_Receive_Perodic(u8*pdata)
{
	if(read_bit(SPSR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	
	return 0;
}

void SPI_Send_NoBlock(u8 data)
{
	SPDR=data;
}
