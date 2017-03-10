
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"
#include <stdio.h>

int getDir(int (*orders)[4][2], int (*elevParam)[3]) {

    printf("          Called getDir().\n");
    int currFloor = *elevParam[0]; 
    int floorAllignment = *elevParam[1];
    int currDir = *elevParam[2];    

    if(currDir != 0) {

    	for (int floor = (currFloor + currDir); (floor < N_FLOORS) && (floor >= 0); floor += currDir) {
        	if (*orders[floor][0] || *orders[floor][1] ) {
            		printf("RETURNED currDir.\n");
            		return currDir;
            	}
        }
    
         
    	if (floorAllignment) {
        	for (int floor = (currFloor - currDir); (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            	if (*orders[floor][0] || *orders[floor][1] ) {
                	printf("RETURNED -currDir.\n");
                	return -(currDir);
            	}
        	}
        	printf("RETURNED 0.\n");
        	return 0;
    	} else { //If not alligned with floor
        	for (int floor = currFloor ; (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            		if (*orders[floor][0] || *orders[floor][1] ) {
                	printf("RETURNED -currDir.\n");
                	return -currDir;
            		}
        	}
        }
    }

        for (int floor = currFloor; (floor < N_FLOORS) && (floor >= 0); floor++) {
            	if (*orders[floor][0] || *orders[floor][1] ) {
                	printf("RETURNED 1.\n");
                	return 1;
                }
        }
        for (int floor = currFloor; (floor < N_FLOORS) && (floor >= 0); floor--) {
            	if (*orders[floor][0] || *orders[floor][1] ) {
                	printf("RETURNED 0.\n");
                	return 0;       
    			}
    	}
    
    printf("------>  Ended up returning 0 \n");
    return 0;
} //getDir

int checkOrder(int (*orders)[4][2], int (*elevParam)[3]) {

   		printf("          Called checkOrder().\n");
    	int currFloor = *elevParam[0]; 
		int currDir = *elevParam[2];

        if (currDir == 1 && *orders[currFloor][0]) {
            printf("RETURNED 1.\n");
            return 1;
    }
                   
        if (currDir == -1 && *orders[currFloor][1]) {
            printf("RETURNED 1.\n");
            return 1;
    }
        
        if (currDir == 0 && (*orders[currFloor][1] || *orders[currFloor][0])) {
            printf("RETURNED 1.\n");
            return 1;
    }
        
        printf("RETURNED 0.\n");
        return 0;
} //checkOrder


void deleteOrder(int (*orders)[4][2], int floor){

        	printf("          Called deleteOrder().\n");
    
 			*orders[floor][0] = *orders[floor][1] = 0;
} //deleteOrder

void newOrder(int (*orders)[4][2], int floor, int type){

       		printf("          Called newOrder() for ");
        	
		if (floor == 0) {
		printf("1st floor.\n");
		}
		else if (floor == 1) {
		printf("2nd floor.\n");
		}
		else if (floor == 2) {
		printf("3rd floor.\n");
		}	
		else if (floor == 3) {
		printf("4th floor.\n");
		}				
    
		if (type == 2) {
		*orders[floor][0] = 1;
		*orders[floor][1] = 1;
		} else {
		*orders[floor][type] = 1;
		}

} //newOrder


        
            
            
