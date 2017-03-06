
#include <stdbool.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "fsm.h"
#include "eventmanager.h"

int newEvent(int stopEvent, int floorEvent, int buttonType, int buttonFloor, int delayEvent) {
    
    
    
    
    if (stopEvent) {
        
        switch(currState) {
                
                
            case WAIT: {
                
            }
                
            case TRANSPORTING: {
                
                elev_set_motor_direction(DIRN_STOP);
            }
                
            case ELEVATOR_ACTIVATOR: {
                
                currState = WAIT;
                
            }
                
            case DOOR_OPEN: {
                
                for (int floor = 0; floor < N_FLOORS; floor++) {
                    deleteOrder(floor);
                }
                
                return 1;
                
            }
                
            case INITIALIZE: {
                
            }
                
            case STOP: {
                
                break;
                
            }
                
            }
                
        }
    
    
    else if (floorEvent) {
        
        fsmCurrFloor = floorEvent;
        
        switch(currState) {
                
            case INITIALIZE: {
                
                currState = WAIT;
                
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
                
                if ( checkOrder(floorEvent, fsmCurrDir) || (getDir(fsmCurrDir, fsmCurrFloor, fsmFloorAlignment) != fsmCurrDir)) {
                    deleteOrder(floorEvent);
                    elev_set_door_open_lamp(1);
                    return 1;
                }
                
            }
                
        }
        
    }
    
    else if (buttonFloor) {
        
        
        switch(currState) {
                
            case STOP: {
                
            }
                
            case INITIALIZE: {
                
                break;
            }
                
            case WAIT: {
                
                currState = ELEVATOR_ACTIVATOR;
            }
                
            case ELEVATOR_ACTIVATOR: {
                
            }
                
            case DOOR_OPEN: {
                
            }
                
            case TRANSPORTING: {
                
                newOrder(buttonType, buttonFloor);
            }
                
        }
        
    }
    
    else if (delayEvent) {
        
        switch (currState) {
                
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
                
                if (!checkOrder(fsmCurrFloor, fsmCurrDir)) {
                    elev_set_door_open_lamp(0);
                    fsmCurrDir = getDir(fsmCurrDir, fsmCurrFloor, fsmFloorAlignment);
                    elev_set_motor_direction(fsmCurrDir);
                    currState = TRANSPORTING;
                }
                else return 1;
            }
                
        }
        
    }
    
    return 0;
    
}








