
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
    for (int floor = currFloor + currDir; (floor <= N_FLOORS) && (floor >= 0); floor += currDir) {
        if (*orders[floor][0] || *orders[floor][1] ) {
            printf("RETURNED currDir.\n");
            return currDir;
            }
        }
    }
         
    if (floorAllignment) {
        
        for (int floor = currFloor - currDir; (floor <= N_FLOORS) && (floor >= 0); floor -= currDir) {
            if (*orders[floor][0] || *orders[floor][1] ) {
                printf("RETURNED -currDir.\n");
                return -currDir;
            }
        }
        printf("RETURNED 0.\n");
        return 0;
    }

    else {
        
        if (currDir != 0) {
        for (int floor = currFloor ; (floor <= N_FLOORS) && (floor >= 0); floor -= currDir) {
            if (*orders[floor][0] || *orders[floor][1] ) {
                printf("RETURNED -currDir.\n");
                return -currDir;
            }
        }
        }
        
        printf("RETURNED 1 AS A TEST.\n");
        return 1;
    }
} //getDir

int checkOrder(int (*orders)[4][2], int (*elevParam)[3]) {

    printf("          Called checkOrder().\n");

    int currFloor = *elevParam[0]; 
	int currDir = *elevParam[2];

        if (currDir == -1 && *orders[currFloor][0]) {
            printf("RETURNED 1.\n");
            return 1;
    }
                   
        if (currDir == 1 && *orders[currFloor][1]) {
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
    
 		for (int orderType = 0; orderType < 2; orderType++){
 			*orders[floor][orderType] = 0;
 		}
} //deleteOrder

void newOrder(int (*orders)[4][2], int floor, int dir){

        char floor_print[2] = {floor, '\0'};
        char dir_print[2] = {dir, '\0'};

        printf("          Called newOrder() for ");
        printf(&floor_print[0], " floor in direction ", &dir_print[0], ".\n");
    
		*orders[floor][dir] = 1;
} //newOrder
        
            
            
