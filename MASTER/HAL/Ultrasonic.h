

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



typedef enum{
	 US1=PINC0,
	 US2=PINC1,
	 US3=PINC2,
	 US4=PINC3
	}ULTRASONIC_type;



void Ultrasonic_Init(void);


u8 Ultrasonic_get_distance(ULTRASONIC_type US,u16*pdistance);
/*u16 ULTRASONIC_GetDistance2(ULTRASONIC_type2 us);*/





#endif /* ULTRASONIC_H_ */