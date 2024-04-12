
#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

typedef enum{
	EX_INT0,
	EX_INT1,
	EX_INT2
	}EX_Interrupt;

typedef enum{
	low_level,
	logical_change,
	falling_edge,
	rising_edge
	}Trigger_edge;






#endif /* EX_INTERRUPT_H_ */