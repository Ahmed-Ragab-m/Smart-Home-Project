
#ifndef SENSORS_H_
#define SENSORS_H_


u16 Read_temp(void);

u16 Read_pressure(void);

void temp_init(void);
void temp_run(void);
u16 tempfiltered(void);
u16 tempunfiltered(void);




#endif /* SENSORS_H_ */