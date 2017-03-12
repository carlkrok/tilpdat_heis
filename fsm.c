
#include <stdbool.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "fsm.h"
#include "eventmanager.h"
#include <time.h>

int newEvent(int stopEvent, int floorEvent, int buttonEvent, int buttonType, int buttonFloor, int delayEvent, int orders[4][2], state_t* currState, int elevParam[], int* prevDebug) {
    
    
    //debugger(1, prevDebug);

    int milisec = 1; // length of time to sleep, in miliseconds
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;



    if (stopEvent) {

    //2printf("   Stop event received in FSM.\n");
    debugger(2, prevDebug);
	elev_set_stop_lamp(1);
	nanosleep(&req, (struct timespec *)NULL);
	elev_set_stop_lamp(0);

	for (int floor = 0; floor < N_FLOORS; floor++) {
                    deleteOrder(orders, floor, prevDebug);
                }
        
        switch(*currState) { 
                            
            case TRANSPORTING: { 
                elev_set_motor_direction(DIRN_STOP);
            }
                
            case ELEVATOR_ACTIVATOR: {
                *currState = WAIT;
                
            }
                
            case INITIALIZE: {
	    	    break;
            }

	    	case WAIT: {
                if (elevParam[1] == 1) {
                    *currState = DOOR_OPEN;
                    elev_set_door_open_lamp(1);
                }
                else {
                    return 0;
                }
            }
                
            case STOP: { 
            }

	    	case DOOR_OPEN: {                  
                return 1;
            }

            } //Switch   
        } //StopEvent
    
    
    else if (floorEvent) {

	floorEvent -= 1;

    	//3printf("   Floor event received in FSM.\n");
        //printf(*prevDebug,'\n','\n');
        debugger(3, prevDebug);

        nanosleep(&req, (struct timespec *)NULL);
        printf("Floorevent = %i \n", floorEvent);
        
        elevParam[0] = floorEvent; //fsmCurrFloor
		elev_set_floor_indicator(floorEvent);
        
        switch(*currState) {
                
            case INITIALIZE: {
                elev_set_motor_direction(DIRN_STOP);
                *currState = WAIT;
				elevParam[1] = 1; //floorAlignment
				elevParam[2] = 0; //currDir
            }
                
            case WAIT: {
            }
                
            case ELEVATOR_ACTIVATOR: {
            }
                
            case DOOR_OPEN: {
            }
                
            case STOP: {
                break;
            }
                
            case TRANSPORTING: {
                
                if ( checkOrder(orders, elevParam, prevDebug) || (getDir(orders, elevParam, prevDebug) != elevParam[2])) {
                    printf("Hallo, jegskal stoppe nå :)\n");
                    elev_set_motor_direction(0);
                    *currState = DOOR_OPEN;
		    		elevParam[1] = 1; //floorAlignment
                    elev_set_door_open_lamp(1);
		    		deleteOrder(orders, elevParam[0], prevDebug);
                    return 1;
                }
                
            }   
        } //switch
    } //floorEvent
    
    else if (buttonEvent) {

    	//4printf("   Button event received in FSM.\n");
        debugger(4, prevDebug);
		nanosleep(&req, (struct timespec *)NULL);	
        
        switch(*currState) {
                
            case STOP: {
            }
                
            case INITIALIZE: {
            	//5printf("--> Initialize state does nothing with button events.\n");
                debugger(5, prevDebug);
                break;
            }
                
            case WAIT: {
            	//6printf("--> Calling newOrder from WAIT state.\n");
                debugger(6, prevDebug);
                newOrder(orders, buttonFloor, buttonType, prevDebug);
                elevParam[2] = getDir(orders, elevParam, prevDebug); //set currDir
                if(elevParam[2]) {
                	elev_set_motor_direction(elevParam[2]); //drive in direction of currDir
                	*currState = TRANSPORTING;
					elevParam[1] = 0;
                }
                break;
            }
                
            case ELEVATOR_ACTIVATOR: {
            }
                
            case DOOR_OPEN: {
            }
                
            case TRANSPORTING: {
            	//7printf("--> Calling newOrder.\n");
                debugger(7, prevDebug);
                newOrder(orders, buttonFloor, buttonType, prevDebug);
            }
        } //switch
    } //buttonEvent
    
    else if (delayEvent) {

    	//8printf("   Delay event received in FSM.\n");
        debugger(8, prevDebug);
        
        switch (*currState) {
                
            case INITIALIZE: {
            }
    
            case ELEVATOR_ACTIVATOR: {
            }
                
            case STOP: {
            }
                
            case TRANSPORTING: {
                printf("! ! ! Delay event in TRANSPORTING state.\n");
                break;
            }

            case WAIT: {
            }
                
            case DOOR_OPEN: {
                printf("Dette er ordrekøen:");
                for (int etasje = 0; etasje < 4; etasje++){
                    printf("\n");
                    for (int i = 0; i < 2; i++){
                        printf("\t%i", orders[etasje][i]);
                    }
                }
                printf("\n");

                int stayInFloor = checkOrder(orders, elevParam, prevDebug);
                printf("Stay in floor: %i \n.", stayInFloor);

                if (!stayInFloor) {
                	//9printf("		Reached delay finished event.");
                    debugger(9, prevDebug);
                    elev_set_door_open_lamp(0);
                    elevParam[2] = getDir(orders, elevParam, prevDebug); //set currDir
		    	     *currState = WAIT;

		    		if(elevParam[2]) {
                    	elev_set_motor_direction(elevParam[2]); //drive in direction of currDir
                    	*currState = TRANSPORTING;
		    			elevParam[1] = 0;
		    	}
                } else {
                	//10printf("		Timer reached trigger but restarted.");
                    debugger(10, prevDebug);
                    deleteOrder(orders, elevParam[0], prevDebug);
                	return 1;
                    //a[b] = a + *(sizeof(int) * b)
                }
            }
                
        } //switch
    } //delayEvent
    
    return 0;
    
}










