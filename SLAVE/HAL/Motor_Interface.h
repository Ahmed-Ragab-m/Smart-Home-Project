

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#include "Memory_Map.h"

typedef enum{
	MOTOR1,
	MOTOR2,
	//MOTOR3,
	//MOTOR4
	}MOTOR_NAME;

void MOTOR_ON_CW(MOTOR_NAME MOTOR);
void MOTOR_ON_CCW(MOTOR_NAME MOTOR);
void MOTOR_STOP(MOTOR_NAME MOTOR);
void servo_motor(u8 position);


#endif /* MOTOR_INTERFACE_H_ */