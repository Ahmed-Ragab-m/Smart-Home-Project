
#ifndef SMART_HOME_H_
#define SMART_HOME_H_

/************************************************************************/
/*                              SLAVE                                   */
/************************************************************************/
#define LED    PINB0
#define FAN    PINB1
#define PUMP   PINB2
#define TV     PINB3
#define Buzzer PINB4
#define Window PIND5

#define LDR    PINA2

/***************************************************************/
void Start_Slave(void);
void OpenLight  (void);
void CloseLight (void);
void OpenFan    (void);
void CloseFan   (void);
void OpenWindow (void);
void CloseWindow(void);
void OpenTV     (void);
void CloseTV    (void);
void OpenPump   (void);
void ClosePump  (void);






#endif /* SMART_HOME_H_ */