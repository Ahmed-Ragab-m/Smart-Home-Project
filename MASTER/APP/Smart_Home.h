
#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#define F_CPU  8000000
#include <util/delay.h>
/************************************************************************/
/*                             MASTER                                   */
/************************************************************************/
#include "stand Types.h"

void StartSmartHome(void);
void SelectUserName(void);
void MaualMode(void);
void AutomaticMode(void);
/*void UserName(void);*/
u16 GetPassword(void);
void EditPassword(void);
void ControlLight(void);
void ControlFan(void);
void ControlTV(void);
void ControlPump(void);
void OpenDoor(void);
void CloseDoor(void);








#endif /* SMART_HOME_H_ */