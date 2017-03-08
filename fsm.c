
#include <stdbool.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "fsm.h"
#include "eventmanager.h"

int newEvent(int stopEvent, int floorEvent, int buttonEvent, int buttonType, int buttonFloor, int delayEvent, int (*orders)[4][2], int* currState, int (*elevParam)[3]) {
    
    
    if (stopEvent) {

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
        
        *elevParam[0] = floorEvent; //fsmCurrFloor
        
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
		    deleteOrder(orders, elevParam);
                    elev_set_door_open_lamp(1);
                    return 1;
                }
                
            }   
        } //switch
    } //floorEvent
    
    else if (buttonEvent) {
        
        switch(*currState) {
                
            case STOP: {
            }
                
            case INITIALIZE: {
                break;
            }
                
            case WAIT: {
            }
                
            case ELEVATOR_ACTIVATOR: {
            }
                
            case DOOR_OPEN: {
            }
                
            case TRANSPORTING: {
                newOrder(orders, buttonFloor, buttonType);
            }
        } //switch
    } //buttonEvent
    
    else if (delayEvent) {
        
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
                    elev_set_door_open_lamp(0);
                    elevParam[2] = getDir(orders, elevParam); //set currDir
                    elev_set_motor_direction(elevParam[2]); //drive in direction of currDir
                    *currState = TRANSPORTING;
                }
                else {return 1;}
            }
                
        } //switch
    } //delayEvent
    
    return 0;
    
}









