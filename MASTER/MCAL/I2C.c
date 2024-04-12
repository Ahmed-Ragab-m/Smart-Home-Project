#include "stand Types.h"
#include "utils.h"
#include "I2C_Private.h"
#include "I2C.h"

/*===========================================================================================================================*/
/*=================================================  [ Master Functions ]   =================================================*/
/*===========================================================================================================================*/
/* Set Master Address to 0 if master will not be addressed */
void I2C_MasterInit (u8 MasterAddress)
{
	Enable_ACK ();           // Enable ACK
	/*===============================================================================*/
	/*  SCL frequency = ( CPU Clock frequency ) / ( 16 + 2(TWBR) * 4^TWPS )          */
	/*  ( 16 + 2(TWBR) * 4^TWPS ) = ( CPU Clock frequency ) / SCL frequency          */
	/*  2(TWBR) * 4^TWPS = ( CPU Clock frequency / SCL frequency ) - 16              */
	/*  TWBR = (( CPU Clock frequency / SCL frequency ) - 16) / ( 2 * 4^TWPS )       */
	/*  // CPU Clock frequency = 8 MHz = 8000000 Hz                                  */
	/*  // SCL frequency = 400 KHz = 400000 Hz     ( Max Speed of TWI )              */
	/*  // TWPS = Value of the prescaler bits in the TWI Status Register (TWSR_REG)  */
	/*  // Prescaller -> 1   ->   0   0   ->  TWPS = 0  ->    4^(0) = 1              */
	/*  // Prescaller -> 4   ->   0   1   ->  TWPS = 1  ->    4^(1) = 4              */
	/*  // Prescaller -> 16  ->   1   0   ->  TWPS = 2  ->    4^(2) = 16             */
	/*  // Prescaller -> 64  ->   1   1   ->  TWPS = 3  ->    4^(3) = 64             */
	/*  TWBR = (( CPU Clock frequency / SCL frequency ) - 16) / ( 2 * 4^TWPS)        */
	/*  TWBR = (( 8000000 / 400000 ) - 16) / ( 2 * 4^(0) )                           */
	/*  TWBR = ( 20 - 16 ) / ( 2 * 1 ) = (4) / (2)                                   */
	/*  TWBR = 2                                                                     */
	/*===============================================================================*/
	TWBR_REG = 2 ;                        // Set TWBR with vale => 400 KHz ( TWBR = 2 )
	// Set prescaller == 1 (clr TWSR 0,1)
	clear_bit(TWSR_REG,TWSR_TWPS0);
	clear_bit(TWSR_REG,TWSR_TWPS1);
	/*Check if the master node will be addressed or not*/
	if( MasterAddress == 0x00 )
	{
		/*Do Nothing*/
	}
	else
	{
		/*Set The Required Address to The Master*/
		TWAR_REG = (MasterAddress << 1);
	}
	// Enable I2C  ( set TWCR 2 )
	set_bit(TWCR_REG,TWCR_TWEN);
}
/*===========================================================================================================================*/
Error_t I2C_Master_StartCondition (void)
{
	Error_t Local_Error = I2C_NO_Error ;
	set_bit(TWCR_REG,TWCR_TWSTA);                               // Start condition ( Set TWCR 5)
	set_bit(TWCR_REG,TWCR_TWINT);                               // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );            // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_START_ACK )     // Check status code == start condition ( TWSR & 0xf8 ) == 0x08
	{
		Local_Error = I2C_Error_Master_StartCond_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_ReStartCondition (void)
{
	Error_t Local_Error = I2C_NO_Error ;
	set_bit(TWCR_REG,TWCR_TWSTA);                                   // Start condition ( Set TWCR 5)
	set_bit(TWCR_REG,TWCR_TWINT);                                   // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_REP_START_ACK )     // Check status code == Repeat condition ( TWSR & 0xf8 ) == 0x10
	{
		Local_Error = I2C_Error_Master_ReStartCond_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_SendSLA_Write_ACK (u8 SlaveAddress)
{
	Error_t Local_Error = I2C_NO_Error ;
	TWDR_REG = (SlaveAddress<<1) ;                                  // Write 7 bits slave address ( TWDR == address<<1 )
	clear_bit(TWDR_REG,TWDR_TWD0);                                  // Write condition ( CLEAR TWDR 0 )
	clear_bit(TWCR_REG,TWCR_TWSTA);                                 // Clear start condition bit ( TWCR 5 ) - for sure
	set_bit(TWCR_REG,TWCR_TWINT);                                   // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_SLA_Write_ACK )     // Check status code == SLA + Write + ACK == (0x18)
	{
		Local_Error = I2C_Error_Master_SendSLA_Write_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_SendSLA_Write_NOTACK (u8 SlaveAddress)
{
	Error_t Local_Error = I2C_NO_Error ;
	Disable_ACK ();                                                    // Disable ACK
	TWDR_REG = (SlaveAddress<<1) ;                                     // Write 7 bits slave address ( TWDR == address<<1 )
	clear_bit(TWDR_REG,TWDR_TWD0);                                     // Write condition ( CLEAR TWDR 0 )
	clear_bit(TWCR_REG,TWCR_TWSTA);                                    // Clear start condition bit ( TWCR 5 ) - for sure
	set_bit(TWCR_REG,TWCR_TWINT);                                      // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                   // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_SLA_Write_NOTACK )     // Check status code == SLA + Write + NOTACK == (0x20)
	{
		Local_Error = I2C_Error_Master_SendSLA_Write_NOTACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_SendSLA_Read_ACK (u8 SlaveAddress)
{
	Error_t Local_Error = I2C_NO_Error ;
	TWDR_REG = (SlaveAddress<<1) ;                                     // Write 7 bits slave address ( TWDR == address<<1 )
	set_bit(TWDR_REG,TWDR_TWD0);                                       // Read condition ( SET TWDR 0 )
	clear_bit(TWCR_REG,TWCR_TWSTA);                                    // Clear start condition bit ( TWCR 5 ) - for sure
	set_bit(TWCR_REG,TWCR_TWINT);                                      // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                    // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_SLA_Read_ACK )         // Check status code == SLA + Read + ACK == (0x40)
	{
		Local_Error = I2C_Error_Master_SendSLA_Read_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_SendSLA_Read_NOTACK (u8 SlaveAddress)
{
	Error_t Local_Error = I2C_NO_Error ;
	Disable_ACK ();                                                    // Disable ACK
	TWDR_REG = (SlaveAddress<<1) ;                                     // Write 7 bits slave address ( TWDR == address<<1 )
	set_bit(TWDR_REG,TWDR_TWD0);                                       // Read condition ( SET TWDR 0 )
	clear_bit(TWCR_REG,TWCR_TWSTA);                                    // Clear start condition bit ( TWCR 5 ) - for sure
	set_bit(TWCR_REG,TWCR_TWINT);                                      // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                   // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_SLA_Read_NOTACK )      // Check status code == SLA + Read + NOTACK == (0x48)
	{
		Local_Error = I2C_Error_Master_SendSLA_Read_NOTACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_WriteDataByte_ACK (u8 WriteData)
{
	Error_t Local_Error = I2C_NO_Error ;
	TWDR_REG = WriteData ;                                              // Write data in TWDR
	set_bit(TWCR_REG,TWCR_TWINT);                                       // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                    // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_WR_DataByte_ACK )       // Check status code == Master Send Data + ACK == (0x28)
	{
		Local_Error = I2C_Error_Master_WriteDataByte_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_WriteDataByte_NOTACK (u8 WriteData)
{
	Error_t Local_Error = I2C_NO_Error ;
	Disable_ACK ();                                                    // Disable ACK
	TWDR_REG = WriteData ;                                      // Write data in TWDR
	set_bit(TWCR_REG,TWCR_TWINT);                                      // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                    // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_WR_DataByte_NOTACK )   // Check status code == Master Send Data + NOTACK == (0x30)
	{
		Local_Error = I2C_Error_Master_WriteDataByte_NOTACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_ReadDataByte_ACK (u8 *ReadData)
{
	Error_t Local_Error = I2C_NO_Error ;
	set_bit(TWCR_REG,TWCR_TWINT);                                       // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                    // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_RD_DataByte_ACK )       // Check status code == Master Read Data + ACK == (0x50)
	{
		Local_Error = I2C_Error_Master_ReadDataByte_ACK ;
	}
	*ReadData = TWDR_REG ;                                               // Read Data From Reg TWDR
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_Master_ReadDataByte_NOTACK (u8 *ReadData)
{
	Error_t Local_Error = I2C_NO_Error ;
	Disable_ACK ();                                                     // Disable ACK
	set_bit(TWCR_REG,TWCR_TWINT);                                       // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                    // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != MASTER_RD_DataByte_NOTACK )    // Check status code == Master Read Data + NOTACK == (0x58)
	{
		Local_Error = I2C_Error_Master_ReadDataByte_NOTACK ;
	}
	*ReadData = TWDR_REG ;                                      // Read Data From Reg TWDR
	return Local_Error ;
}
/*===========================================================================================================================*/
void I2C_Master_StopCondition (void)
{
	set_bit(TWCR_REG,TWCR_TWSTO);               // Stop condition ( Set TWCR 4 )
	set_bit(TWCR_REG,TWCR_TWINT);               // Clear flag ( Set TWCR 7 )
}

/*===========================================================================================================================*/
/*=================================================   [ Slave Functions ]   =================================================*/
/*===========================================================================================================================*/
/*===========================================================================================================================*/
void I2C_SlaveInit (u8 SlaveAddress)
{
	TWAR_REG = SlaveAddress << 1 ;       // Set slave address in ( TWAR = address<<1 )
	Enable_ACK();                               // Enable ACK  ( set TWCR 6 )
	set_bit(TWCR_REG,TWCR_TWEN);                // Enable I2C  ( set TWCR 2 )
}
/*===========================================================================================================================*/
Error_t I2C_SLAVE_OwnSLA_Write_Recieved_ACK (void)
{
	Error_t Local_Error = I2C_NO_Error ;
	set_bit(TWCR_REG,TWCR_TWINT);                                             // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                          // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != SLAVE_OwnSLA_Write_Recieved_ACK )   // Check status code == Own Slave Address + Write + ACK == (0x60)
	{
		Local_Error = I2C_Error_Slave_OwnSLA_Write_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_SLAVE_OwnSLA_Read_Recieved_ACK (void)
{
	Error_t Local_Error = I2C_NO_Error ;
	set_bit(TWCR_REG,TWCR_TWINT);                                             // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                          // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != SLAVE_OwnSLA_Read_Recieved_ACK )     // Check status code == Own Slave Address + Read + ACK == (0xA8)
	{
		Local_Error = I2C_Error_Slave_OwnSLA_Read_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_SLAVE_DataByteRecieved_ACK (u8 *RecievedData)
{
	Error_t Local_Error = I2C_NO_Error ;
	set_bit(TWCR_REG,TWCR_TWINT);                                             // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                          // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != SLAVE_DataByte_Recieved_ACK )        // Check status code == Data Byte Recived + ACK  == (0x80)
	{
		Local_Error = I2C_Error_Slave_DataByteRecieved_ACK ;
	}
	*RecievedData = TWDR_REG ;                                        // Read Data From Reg TWDR
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_SLAVE_DataByteRecieved_NOTACK (u8 *RecievedData)
{
	Error_t Local_Error = I2C_NO_Error ;
	Disable_ACK ();                                                             // Disable ACK
	set_bit(TWCR_REG,TWCR_TWINT);                                               // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                            // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != SLAVE_DataByte_Recieved_NOTACK )       // Check status code == Data Byte Recived + NOTACK  == (0x88)
	{
		Local_Error = I2C_Error_Slave_DataByteRecieved_NOTACK ;
	}
	*RecievedData = TWDR_REG ;                                                  // Read Data From Reg TWDR
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_SLAVE_DataByteTransmit_ACK (u8 TransmitData)
{
	Error_t Local_Error = I2C_NO_Error ;
	TWDR_REG =  TransmitData ;                                               // Write Data in Reg TWDR
	set_bit(TWCR_REG,TWCR_TWINT);                                            // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                          // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != SLAVE_DataByte_Transmitted_ACK )    // Check status code == Data Byte Transmit + ACK  == (0xB8)
	{
		Local_Error = I2C_Error_Slave_DataByteTransmit_ACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
Error_t I2C_SLAVE_DataByteTransmit_NOTACK (u8 TransmitData)
{
	Error_t Local_Error = I2C_NO_Error ;
	Disable_ACK ();                                                              // Disable ACK
	TWDR_REG =  TransmitData ;                                                   // Write Data in Reg TWDR
	set_bit(TWCR_REG,TWCR_TWINT);                                                // Clear flag ( Set TWCR 7 )
	while( ( read_bit(TWCR_REG,TWCR_TWINT) ) == 0 );                             // Wait for flag ( TWCR 7 == 0 )
	if ( (TWSR_REG & STATUS_BIT_MASK) != SLAVE_DataByte_Transmitted_NOTACK )     // Check status code == Data Byte Transmit + NOTACK  == (0xC0)
	{
		Local_Error = I2C_Error_Slave_DataByteTransmit_NOTACK ;
	}
	return Local_Error ;
}
/*===========================================================================================================================*/
void Enable_ACK (void)
{
	// Enable ACK  ( Set TWCR 6 )
	set_bit(TWCR_REG,TWCR_TWEA);
}
/*===========================================================================================================================*/
void Disable_ACK (void)
{
	// Disable ACK  ( Clear TWCR 6 )
	clear_bit(TWCR_REG,TWCR_TWEA);
}
/*===========================================================================================================================*/


