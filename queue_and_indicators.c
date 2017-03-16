
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"
#include <stdio.h>

int getDir(int orders[4][2], int elevParam[]) {

    //For better readibility.
    int currFloor = elevParam[0];
    int floorAllignment = elevParam[1];
    int currDir = elevParam[2]; 

    if(currDir != 0) { //Current direction is prioritized. 

    	for (int floor = (currFloor + currDir); (floor < N_FLOORS) && (floor >= 0); floor += currDir) {
        	
            if (orders[floor][0] || orders[floor][1] ) { 
            		return currDir;
            	}
        }
    
         
    	if (floorAllignment) {
        	for (int floor = (currFloor - currDir); (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            		if (orders[floor][0] || orders[floor][1] ) {
                		return -currDir;
            		}
        	}
               	return 0;

    	} else { //If not alligned with floor      
        	for (int floor = currFloor ; (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            		if (orders[floor][0] || orders[floor][1] ) {
                         	return -currDir;
            		}
        	}
        }
    } else {//End of current direction prioritation procedure. 

	//Checks for orders above the current floor.
        for (int floor = currFloor; (floor < N_FLOORS) && (floor >= 0); floor++) {
            	if (orders[floor][0] || orders[floor][1] ) {
                	return 1;
                }
        }

	//Checks for orders below the current floor.
        for (int floor = currFloor; (floor < N_FLOORS) && (floor >= 0); floor--) {
            	if (orders[floor][0] || orders[floor][1] ) {
                	return -1;       
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
        if (currDir == 1 && orders[currFloor][0]) {
            return 1;
	}
                   
        if (currDir == -1 && orders[currFloor][1]) {
            return 1;
	}
        
        if (currDir == 0 && (orders[currFloor][1] || orders[currFloor][0])) {
            return 1;
	}
        
	return 0;
}

void deleteOrder(int orders[4][2], int floor){
	
	orders[floor][0] = 0;
	orders[floor][1] = 0;

	/*Following code turns off the relevant button lights*/
	elev_set_button_lamp(2, floor, 0);

	if (!(floor == 0)){
		elev_set_button_lamp(1 , floor, 0);
	}
	if (!(floor == 3)){
		elev_set_button_lamp(0 , floor, 0);
	}
            
            
}

void newOrder(int orders[4][2], int floor, int type){	

        elev_set_button_lamp(type, floor, 1);

	if (type == 2) {
		orders[floor][0] = 1;
		orders[floor][1] = 1;
	} else {
		orders[floor][type] = 1;
	}

}

        
            
            
