
#ifndef fsm_h
#define fsm_h

#include <stdio.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"


int newEvent(int stopEvent, int floorEvent, int buttonType, int buttonFloor, int delayEvent);

#endif /* fsm_h */
