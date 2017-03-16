
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"
#include <stdio.h>

int getDir(int orders[4][2], int elevParam[]) {

    //For better readibility.
    int currFloor = elevParam[0];
    int floorAllignment = elevParam[1];
    int currDir = elevParam[2]; 

    //Current direction is prioritized. 
    if(currDir != DIRN_STOP) { 

        //Checks if there is any orders beyond current floor in current direction
    	for (int floor = (currFloor + currDir); (floor < N_FLOORS) && (floor >= 0); floor += currDir) {
        	
            if (orders[floor][OrderUp] || orders[floor][OrderDown] ) { 
            		return currDir;
            	}
        }
    
        
    	if (floorAllignment) {
        	for (int floor = (currFloor - currDir); (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            		if (orders[floor][OrderUp] || orders[floor][OrderDown] ) {
                		return -currDir;
            		}
        	}
               	return 0;

    	} 
        //If elevator has stopped between floors
        else {     
        	for (int floor = currFloor ; (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            		if (orders[floor][OrderUp] || orders[floor][OrderDown] ) {
                         	return -currDir;
            		}
        	}
        }
        
    }

    //If there is no current direction.
    else {

	//Checks for orders above the current floor.
        for (int floor = currFloor + 1; (floor < N_FLOORS) && (floor >= 0); floor++) {
            	if (orders[floor][OrderUp] || orders[floor][OrderDown] ) {
                	return DIRN_UP;
                }
        }

	//Checks for orders below the current floor.
        for (int floor = currFloor - 1; (floor < N_FLOORS) && (floor >= 0); floor--) {
            	if (orders[floor][OrderUp] || orders[floor][OrderDown] ) {
                	return DIRN_DOWN;       
    		}
    	}
    }
    return 0;

}

int checkOrder(int orders[4][2], int elevParam[]) {

	//For better readibility.
    int currFloor = elevParam[0]; 
	int currDir = elevParam[2];

	/*Follorwing code checks if there is an order in the same direction as the elevator.*/
        if (currDir == DIRN_UP && orders[currFloor][OrderUp]) {
            return 1;
	}
                   
        if (currDir == DIRN_DOWN && orders[currFloor][OrderDown]) {
            return 1;
	}
        
        if (currDir == DIRN_STOP && (orders[currFloor][OrderUp] || orders[currFloor][OrderDown])) {
            return 1;
	}
        
	return 0;
}

void deleteOrder(int orders[4][2], int floor){
	
	orders[floor][OrderUp] = 0;
	orders[floor][OrderDown] = 0;

	/*Following code turns off the relevant button lights*/
	elev_set_button_lamp(2, floor, 0);

	if (floor != 0){
		elev_set_button_lamp(1 , floor, 0);
	}
	if (floor != 3){
		elev_set_button_lamp(0 , floor, 0);
	}
            
            
}

void setOrder(int orders[4][2], int orderFloor, int orderType){	

        elev_set_button_lamp(orderType, orderFloor, 1);

	if (orderType == BUTTON_COMMAND) {
		orders[orderFloor][OrderUp] = 1;
		orders[orderFloor][OrderDown] = 1;
	} else {
		orders[orderFloor][orderType] = 1;
	}

}

        
            
            
