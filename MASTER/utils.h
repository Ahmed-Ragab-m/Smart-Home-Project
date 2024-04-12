
#ifndef UTILS_H_
#define UTILS_H_

/* -------------------------------BITWISE operation ---------------------------*/
#define  set_bit(reg,bit)      (reg=reg|(1<<bit))
#define  clear_bit(reg,bit)    (reg=reg&~(1<<bit))
#define  toggle_bit(reg,bit)    (reg=reg^(1<<bit))
#define  read_bit(reg,bit)      ((reg>>bit)&1)






#endif /* UTILS_H_ */