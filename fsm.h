
#pragma once

#include <stdio.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"


int newEvent(int stopEvent, int floorEvent, int buttonEvent, int buttonType, int buttonFloor, int delayEvent, int (*orders)[4][2], state_t* currState, int (*elevParam)[3]);
