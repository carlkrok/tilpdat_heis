
#pragma once

#include <stdio.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"


int newEvent(int stopEvent, int floorEvent, int buttonType, int buttonFloor, int delayEvent, int (*orders)[4][2], int* currState);