
#include "elev.h"
#include <stdio.h>
#include "eventmanager.h"
#include "fsm.h"
#include <time.h>


int eventManager() {
    int sec = 0, trigger = 3, delayState = 0;
    clock_t startTime;

    int floorSensorSignal;
    int delayRequest = 0;

    enum state currState = INITIALIZE;
    
    int orders[N_FLOORS][2] = {0};

    int elevParam[3] = {0};
    
    while(1) {
            
    		if (elev_get_stop_signal()){
    			delayRequest = newEvent( 1, 0, 0, 0, 0, 0, &orders, &currState, &elevParam);
    		} //stopSignal

    		if ((floorSensorSignal = elev_get_floor_sensor_signal()) > -1){
		  delayRequest = newEvent( 0, floorSensorSignal, 0, 0, 0, 0, &orders, &currState, &elevParam);
    		} //floorSensorSignal
    		
            for (int type = 0; type < 3; type++){
                
				for (int floor = 0; floor < N_FLOORS; floor++){
                    
					if (elev_get_button_signal(type, floor)){
						delayRequest = newEvent( 0, 0, 1, type, floor, 0, &orders, &currState, &elevParam);
					}
				}
			} //buttonSignal
        
        
            if (delayRequest) {
                
                if (!delayState) {
                    delayState = 1;
                    startTime = clock();
                }
                
                clock_t timeDifference = clock() - startTime;
                sec = timeDifference / CLOCKS_PER_SEC;
                if (sec >= trigger) {
                    delayState = 0;
                    delayRequest = newEvent(0, 0, 0, 0, 0, 1, &orders, &currState, &elevParam);
                }
                
            } //handle delay (door open)
			
    } //while 1

    return 0;
}


