
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"

int getDir(int (*orders)[4][2], int (*elevParam)[3]) {

    int currFloor = *elevParam[0]; 
    int floorAlignment = *elevParam[1];
    int currDir = *elevParam[2];    

    for (int floor = currFloor + currDir; (floor <= N_FLOORS) && (floor >= 0); floor += currDir) {
        if (*orders[floor][0] || *orders[floor][1] ) return currDir;
    }
         
    if (floorAllignment) {
        
        for (int floor = currFloor - currDir; (floor <= N_FLOORS) && (floor >= 0); floor -= currDir) {
            if (*orders[floor][0] || *orders[floor][1] ) return -currDir;
        }
        return 0;
    }

    else {
        
        for (int floor = currFloor ; (floor <= N_FLOORS) && (floor >= 0); floor -= currDir) {
            if (*orders[floor][0] || *orders[floor][1] ) return -currDir;
        }
        return 0;
    }
} //getDir

int checkOrder(int (*orders)[4][2], int (*elevParam)[3]) {

    	int currFloor = *elevParam[0]; 
	int currDir = *elevParam[2];

        if (currDir == -1 && *orders[currFloor][0]) {return 1;}
                   
        if (currDir == 1 && *orders[currFloor][1]) {return 1;}
        
        if (currDir == 0 && (*orders[currFloor][1] || *orders[currFloor][0])) {return 1;}
        
        return 0;
} //checkOrder


void deleteOrder(int (*orders)[4][2], int floor){
    
 		for (int orderType = 0; orderType < 2; orderType++){
 			*orders[floor][orderType] = 0;
 		}
} //deleteOrder

void newOrder(int (*orders)[4][2], int floor, int dir){
    
		*orders[floor][dir] = 1;
} //newOrder
        
            
            
