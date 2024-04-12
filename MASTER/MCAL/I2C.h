
#ifndef I2C_H_
#define I2C_H_

typedef enum
{
	I2C_NO_Error ,
	I2C_Error_Master_StartCond_ACK ,
	I2C_Error_Master_ReStartCond_ACK ,
	I2C_Error_Master_SendSLA_Write_ACK ,
	I2C_Error_Master_SendSLA_Write_NOTACK ,
	I2C_Error_Master_SendSLA_Read_ACK ,
	I2C_Error_Master_SendSLA_Read_NOTACK ,
	I2C_Error_Master_WriteDataByte_ACK ,
	I2C_Error_Master_WriteDataByte_NOTACK ,
	I2C_Error_Master_ReadDataByte_ACK ,
	I2C_Error_Master_ReadDataByte_NOTACK ,
	I2C_Error_Slave_OwnSLA_Write_ACK ,
	I2C_Error_Slave_OwnSLA_Read_ACK ,
	I2C_Error_Slave_DataByteRecieved_ACK ,
	I2C_Error_Slave_DataByteRecieved_NOTACK ,
	I2C_Error_Slave_DataByteTransmit_ACK ,
	I2C_Error_Slave_DataByteTransmit_NOTACK ,
}Error_t ;
/*===================================================================*/
/*======================   Master Functions  ========================*/
/*===================================================================*/
void I2C_MasterInit (u8 MasterAddress);
Error_t I2C_Master_StartCondition (void);
Error_t I2C_Master_ReStartCondition (void);
Error_t I2C_Master_SendSLA_Write_ACK (u8 SlaveAddress);
Error_t I2C_Master_SendSLA_Write_NOTACK (u8 SlaveAddress);
Error_t I2C_Master_SendSLA_Read_ACK (u8 SlaveAddress);
Error_t I2C_Master_SendSLA_Read_NOTACK (u8 SlaveAddress);
Error_t I2C_Master_WriteDataByte_ACK (u8 WriteData);
Error_t I2C_Master_WriteDataByte_NOTACK (u8 WriteData);
Error_t I2C_Master_ReadDataByte_ACK (u8 *ReadData);
Error_t I2C_Master_ReadDataByte_NOTACK (u8 *ReadData);
void I2C_Master_StopCondition (void);
/*===================================================================*/
/*=======================   Slave Functions   =======================*/
/*===================================================================*/
void I2C_SlaveInit (u8 SlaveAddress);
Error_t I2C_SLAVE_OwnSLA_Write_Recieved_ACK (void);
Error_t I2C_SLAVE_OwnSLA_Read_Recieved_ACK (void);
Error_t I2C_SLAVE_DataByteRecieved_ACK (u8 *RecievedData);
Error_t I2C_SLAVE_DataByteRecieved_NOTACK (u8 *RecievedData);
Error_t I2C_SLAVE_DataByteTransmit_ACK (u8 TransmitData);
Error_t I2C_SLAVE_DataByteTransmit_NOTACK (u8 TransmitData);
/*===================================================================*/
void Enable_ACK (void);
void Disable_ACK (void);
/*===================================================================*/




#endif /* I2C_H_ */