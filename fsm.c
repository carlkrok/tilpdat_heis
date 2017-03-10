
#include <stdbool.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "fsm.h"
#include "eventmanager.h"
#include <time.h>

int newEvent(int stopEvent, int floorEvent, int buttonEvent, int buttonType, int buttonFloor, int delayEvent, int (*orders)[4][2], state_t* currState, int (*elevParam)[3]) {
    
    char state_names[8] = {'I', 'W', 'E', 'D', 'S', 'T', '\n', '\0'};
    int this_state = *currState;
    printf("******** Current state is: ");
    printf(&state_names[this_state]);

    int milisec = 200; // length of time to sleep, in miliseconds
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;

    
    if (stopEvent) {

    printf("   Stop event received in FSM.\n");
	elev_set_stop_lamp(1);
	nanosleep(&req, (struct timespec *)NULL);
	elev_set_stop_lamp(0);

	for (int floor = 0; floor < N_FLOORS; floor++) {
                    deleteOrder(orders, floor);
                }
        
        switch(*currState) { 
                            
            case TRANSPORTING: { 
                elev_set_motor_direction(DIRN_STOP);
            }
                
            case ELEVATOR_ACTIVATOR: {
                *currState = WAIT;
                
            }
                
            case INITIALIZE: {
	    	}

	    	case WAIT: {  
            }
                
            case STOP: { 
                break;
            }

	    	case DOOR_OPEN: {                  
                return 1;
            }

            } //Switch   
        } //StopEvent
    
    
    else if (floorEvent) {

    	printf("   Floor event received in FSM.\n");
        
        *elevParam[0] = floorEvent; //fsmCurrFloor
		elev_set_floor_indicator(floorEvent);
        
        switch(*currState) {
                
            case INITIALIZE: {
                elev_set_motor_direction(DIRN_STOP);
                *currState = WAIT;
				*elevParam[1] = 1; //floorAlignment
				*elevParam[2] = 0; //currDir
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
                
                if ( checkOrder(orders, elevParam) || (getDir(orders, elevParam) != *elevParam[2])) {
                    elev_set_motor_direction(DIRN_STOP);
                    *currState = DOOR_OPEN;
		    		*elevParam[1] = 1; //floorAlignment
		    		deleteOrder(orders, *elevParam[0]);
                    elev_set_door_open_lamp(1);
                    return 1;
                }
                
            }   
        } //switch
    } //floorEvent
    
    else if (buttonEvent) {

    	printf("   Button event received in FSM.\n");
		nanosleep(&req, (struct timespec *)NULL);	
        
        switch(*currState) {
                
            case STOP: {
            }
                
            case INITIALIZE: {
            	printf("--> Initialize state does nothing with button events.\n");
                break;
            }
                
            case WAIT: {
            	printf("--> Calling newOrder from WAIT state.\n");
                newOrder(orders, buttonFloor, buttonType);
                *elevParam[2] = getDir(orders, elevParam); //set currDir
                if(*elevParam[2]) {
                	elev_set_motor_direction(*elevParam[2]); //drive in direction of currDir
                	*currState = TRANSPORTING;
					*elevParam[1] = 0;
                }
                break;
            }
                
            case ELEVATOR_ACTIVATOR: {
            }
                
            case DOOR_OPEN: {
            }
                
            case TRANSPORTING: {
            	printf("--> Calling newOrder.\n");
                newOrder(orders, buttonFloor, buttonType);
            }
        } //switch
    } //buttonEvent
    
    else if (delayEvent) {

    	printf("   Delay event received in FSM.\n");
        
        switch (*currState) {
                
            case INITIALIZE: {
            }
                
            case WAIT: {
            }
                
            case ELEVATOR_ACTIVATOR: {
            }
                
            case STOP: {
            }
                
            case TRANSPORTING: {
                break;
            }
                
            case DOOR_OPEN: {
                if (!checkOrder(orders, elevParam)) {
                	printf("		Reached delay finished event.");
                    elev_set_door_open_lamp(0);
                    *elevParam[2] = getDir(orders, elevParam); //set currDir
		    	
		    		if(*elevParam[2]) {
                    	elev_set_motor_direction(*elevParam[2]); //drive in direction of currDir
                    	*currState = TRANSPORTING;
		    			*elevParam[1] = 0;
		    	}
                } else {
                	printf("		Timer reached trigger but restarted.");
                	return 1;
                }
            }
                
        } //switch
    } //delayEvent
    
    return 0;
    
}









