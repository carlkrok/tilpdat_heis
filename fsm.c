#include <stdbool.h>
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"
#include <time.h>
#include "fsm.h"

//Only one event is true for each newEvent.
int newEvent(int stopEvent, int floorEvent, int buttonEvent, int buttonType, int buttonFloor, int delayEvent, int orders[4][2], state_t* currState, int elevParam[]) {
    

	//Length of time to sleep, in miliseconds
    int milisec = 1; 
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;

 
    if (stopEvent) {

 	//Turns stoplamp on for a short time
	elev_set_stop_lamp(1);
	nanosleep(&req, (struct timespec *)NULL);
	elev_set_stop_lamp(0);


	for (int floor = 0; floor < N_FLOORS; floor++) {
                    deleteOrder(orders, floor);
                }
        
        switch(*currState) { 
                            
            case TRANSPORTING: { 
                elev_set_motor_direction(DIRN_STOP);
                *currState = WAIT;
            }

                
            case INITIALIZE: {
	    	    break;
            }

	    	case WAIT: {

	    		//Opens the door and resets timer if elevator is on a floor
                if (elevParam[1]) { 
                    *currState = DOOR_OPEN;
                    elev_set_door_open_lamp(1);
                    return 1;
                }
                else {
                    return 0;
                }
            }

	    	case DOOR_OPEN: {                  
                return 1; //Resets timer
            }

            } //Switch   
        } //StopEvent


    else if (floorEvent) {
    	//Floorevent is subtracted 1 so it represents the correct floor.
		floorEvent -= 1;

        nanosleep(&req, (struct timespec *)NULL);
        elevParam[0] = floorEvent; //sets current floor.
		elev_set_floor_indicator(floorEvent);
        
        switch(*currState) {

            case TRANSPORTING: {

			    if (checkStop(orders, elevParam)) {
			       
			        elev_set_motor_direction(DIRN_STOP);
			        *currState = DOOR_OPEN;
					elevParam[1] = 1; //Elevator is alligned with floor.
			        elev_set_door_open_lamp(1);
					deleteOrder(orders, elevParam[0]);
			        return 1;
			    }
    			break;
    		}

            case INITIALIZE: {
                elev_set_motor_direction(DIRN_STOP);
                *currState = WAIT;
				elevParam[1] = 1; //Elevator is alligned with floor.
				elevParam[2] = DIRN_STOP; //Sets direction to 0.
            }
                
            case WAIT: {
            }
                
            case DOOR_OPEN: {
            	break;
            }
                
  
        } //switch
    } //floorEvent
    




    else if (buttonEvent) {
       
		nanosleep(&req, (struct timespec *)NULL);	
        
        switch(*currState) {


        	case TRANSPORTING: {        	
            }
                 
            case DOOR_OPEN: {
            	setOrder(orders, buttonFloor, buttonType);
            	break;
            }              
                
            case INITIALIZE: {
                break;
            }
                
            case WAIT: {
               
                setOrder(orders, buttonFloor, buttonType);
                elevParam[2] = getDir(orders, elevParam); //set currDir


                //Starts driving if order is on another floor
                if(elevParam[2]) {
                	elev_set_motor_direction(elevParam[2]); 
                	*currState = TRANSPORTING;
					elevParam[1] = 0; //Elevator is no longer Allingned with floor
                }
                break;
            }
                
        } //switch
    } //buttonEvent
    



    else if (delayEvent) {
       
        switch (*currState) {
                
            case TRANSPORTING: {
            }
    
                
            case INITIALIZE: { 
                break;
            }

            case WAIT: {
            }
                
            case DOOR_OPEN: {
            	//For better readibility.
                int stayInFloor = checkOrder(orders, elevParam);

                if (!stayInFloor) {
                    
                    elev_set_door_open_lamp(0);
                    elevParam[2] = getDir(orders, elevParam); //set currDir
		    	     *currState = WAIT;


		    		if(elevParam[2]) {
                    	elev_set_motor_direction(elevParam[2]); //drive in direction of currDir
                    	*currState = TRANSPORTING;
		    			elevParam[1] = 0; //Elevator is no longer Allingned with floor
		    	}
                } else {
                    
                    deleteOrder(orders, elevParam[0]);
                	return 1;
                }
            }
                
        } //switch
    } //delayEvent
    
    return 0;
    
}




int checkStop(int orders[4][2], int elevParam[4]){
	if ( checkOrder(orders, elevParam) || (getDir(orders, elevParam) != elevParam[2])) {
        return 1;
	}
	else{
		return 0;
	}
}



