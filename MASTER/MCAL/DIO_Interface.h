

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

typedef enum{         //  DIO PORTS
	PA,
	PB,
	PC,
	PD
}DIO_PORT;

typedef enum{         //  PIN STATUS
	INFREE,
	INPULL_UP,
	OUTPUT
}PIN_STATUS;

typedef enum{         //  PIN VOLT
	LOW,
	HIGH
	}PIN_VOLT;

typedef enum{         // DIO PINS 
	PINA0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_PINS;

void DIO_Initialize_PIN(DIO_PINS PIN,PIN_STATUS status);
void DIO_Write_pin(DIO_PINS PIN,PIN_VOLT volt);
PIN_VOLT DIO_READ_pin(DIO_PINS PIN);
void DIO_Init(void);
void DIO_Write_Port(DIO_PORT PORT,char data);
void DIO_Toggle_PIN(DIO_PINS PIN);


#endif /* DIO_INTERFACE_H_ */