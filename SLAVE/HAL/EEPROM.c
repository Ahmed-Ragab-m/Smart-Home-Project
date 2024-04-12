#include "stand Types.h"
#include "DIO_Interface.h"
#include "I2C.h"
#include "EEPROM.h"



void EEPROM_WriteData(u16 address,u8 data)
{
	 u8 Local_Address ;
	 Local_Address = EEPROM_FIXED_ADDRESS | (EEPROM_A2<<2) | ((u8)(address>>8)) ;
	 // Send Start Condition
	 I2C_Master_StartCondition ();
	 // Send the address packet
	 I2C_Master_SendSLA_Write_ACK (Local_Address);
	 // send the rest 8 BITS of the location Adress
	 I2C_Master_WriteDataByte_ACK ( (u8)(address));
	 // Send The Data Byte to the Memory Location
	 I2C_Master_WriteDataByte_ACK (data);
	 // Send Stop Condition
	 I2C_Master_StopCondition ();
	 // Delay Until the Write cycle is finished
	 _delay_ms(10);
}

u8 EEPROM_ReadData(u16 address)
{
	 u8 Data ;
	 u8 Local_Address ;
	 Local_Address = EEPROM_FIXED_ADDRESS | (EEPROM_A2<<2) | ((u8)(address>>8)) ;
	 // Send Start Condition
	 I2C_Master_StartCondition ();
	 // Send the address packet with Write operation
	 I2C_Master_SendSLA_Write_ACK (Local_Address);
	 // send the rest 8 BITS of the location Adress
	 I2C_Master_WriteDataByte_ACK ( (u8)(address) );
	 // Send Repeated Start to chang write request to Read request
	 I2C_Master_ReStartCondition ();
	 // Send the address packet with Read operation
	 I2C_Master_SendSLA_Read_ACK (Local_Address);
	 // Get The Data From Memory
	 I2C_Master_ReadDataByte_NOTACK (&Data);
	 // Send Stop Condition
	 I2C_Master_StopCondition();
	 // Delay Until the Read cycle is finished
	 _delay_ms(10);
	 // Return Data
	 return Data ;
}