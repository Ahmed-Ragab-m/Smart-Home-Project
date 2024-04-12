

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define  first_output PINA0
#define  first_input  PINA4

#define  row    4
#define  col    4
#define no_key  'T'

#ifdef   Keypad_Interface
u8 keypad_arr[row][col]={{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'c','0','=','+'}};
#endif







#endif /* KEYPAD_CONFIG_H_ */