
#ifndef EEPROM_H_
#define EEPROM_H_

#define F_CPU  8000000
#include <util/delay.h>

#define  EEPROM_FIXED_ADDRESS 0b1010000
#define  EEPROM_A2    0

void EEPROM_WriteData(u16 address,u8 data);

u8 EEPROM_ReadData(u16 address);


#endif /* EEPROM_H_ */