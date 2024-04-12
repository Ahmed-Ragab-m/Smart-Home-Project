
#ifndef SPI_H_
#define SPI_H_

typedef enum{
	MASTER,
	SLAVE
	}SPI_Mode;

void SPI_Int(SPI_Mode mode);

u8 SPI_Send_Recieve(u8 data);

u8 SPI_Receive_Perodic(u8*pdata);

void SPI_Send_NoBlock(u8 data);




#endif /* SPI_H_ */