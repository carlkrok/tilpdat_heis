
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

    state_t currState = INITIALIZE;

    printf("+++ State is now INITIALIZE. +++\n");
    
    int orders[N_FLOORS][2] = {0};
    int elevParam[3] = {0, 0, 1};

    elev_set_motor_direction(1); //Initialize driving.
    
    while(!elev_get_obstruction_signal()) {
            
    		if (elev_get_stop_signal()){
                printf("Got a stop signal.\n");
    			delayRequest += newEvent( 1, 0, 0, 0, 0, 0, &orders, &currState, &elevParam);
    		} //stopSignal

    		if (((floorSensorSignal = elev_get_floor_sensor_signal()) != -1) && !(elevParam[1])){
                printf("Got a floor sensor signal.\n");
                delayRequest += newEvent( 0, floorSensorSignal, 0, 0, 0, 0, &orders, &currState, &elevParam);
    		} //floorSensorSignal
    		
           	for (int buttonType = 0; buttonType < 3; buttonType++){
				for (int floor = 0; floor < N_FLOORS; floor++){
					if (!((floor == 0 && buttonType == 1) || (floor == 3 && buttonType == 0)) && elev_get_button_signal(buttonType, floor)){
						printf("Got a button signal.\n");
                        			delayRequest += newEvent( 0, 0, 1, buttonType, floor, 0, &orders, &currState, &elevParam);
					}
				}
			} //buttonSignal
        
        
            if (delayRequest) {

		printf("----------------------\nReceived a delay request!\n");
                
                if (!delayState) {
                    delayState = 1;
                    startTime = clock();
                    printf("Starting timer.\n");
                }
                
                clock_t timeDifference = clock() - startTime;
                sec = timeDifference / CLOCKS_PER_SEC;
                if (sec >= trigger) {
                    delayState = 0;
                    printf("----------------------\nTimer reached trigger.\n");
                    delayRequest = newEvent(0, 0, 0, 0, 0, 1, &orders, &currState, &elevParam);
                }
                
            } //handle delay (door open)
			
    } //while 1

    return 0;
}


