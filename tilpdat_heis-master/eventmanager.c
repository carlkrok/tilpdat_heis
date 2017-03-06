
#include "elev.h"
#include <stdio.h>
#include "eventmanager.h"
#include "fsm.h"
#include <time.h>


int eventManager() {
    int sec = 0, trigger = 3, delay = 0;
    clock_t startTime;
    int floorSensorSignal;
    int doorDelay = 0;

    enum state currState = INITIALIZE;
    
    int orders[N_FLOORS][2] = {0};
    
    while(1) {
            
    		if (elev_get_stop_signal()){
    			doorDelay = newEvent( 1, 0, 0, 0, 0, &orders, &currState);
    		}

    		if ((floorSensorSignal = elev_get_floor_sensor_signal()) > -1){
		  doorDelay = newEvent( 0, floorSensorSignal, 0, 0, 0, &orders, &currState);
    		}
    		
            for (int type = 0; type < 3; type++){
                
				for (int floor = 0; floor < N_FLOORS; floor++){
                    
					if (elev_get_button_signal(type, floor)){
						 doorDelay = newEvent( 0, 0, type, floor, 0, &orders, &currState);
					}
				}
			}
        
        
            if (doorDelay) {
                
                if (!delay) {
                    delay = 1;
                    startTime = clock();
                }
                
                clock_t timeDifference = clock() - startTime;
                sec = timeDifference / CLOCKS_PER_SEC;
                if (sec >= trigger) {
                    delay = 0;
                    doorDelay = newEvent(0, 0, 0, 0, 1, &orders, &currState);
                }
                
            }
			
    }
    return 0;
}


