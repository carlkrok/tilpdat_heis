
#pragma once
#include "queue_and_indicators.h"
#include "eventmanager.h"


//State machine that decides what should happen when the eventmanager sends an event.
int newEvent(int stopEvent, int floorEvent, int buttonEvent, int buttonType, int buttonFloor, int delayEvent, int orders[4][2], state_t* currState, int elevParam[]);

//Returns 1 if the elevator should stop at a floor. Otherwise 0.  
int checkStop(int orders[4][2], int elevParam[4]);

