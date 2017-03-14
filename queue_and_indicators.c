
#include "queue_and_indicators.h"
#include "elev.h"
#include "eventmanager.h"
#include <stdio.h>

int getDir(int orders[4][2], int elevParam[], int* prevDebug) {

    //14printf("          Called getDir().\n");
    debugger(14, prevDebug);
    int currFloor = elevParam[0];
    printf( "currFloor = %i \n", currFloor); 
    int floorAllignment = elevParam[1];
    int currDir = elevParam[2]; 

    //printf(&currDir);  
    printf("Dette er ordrekøen:");
    for (int etasje = 0; etasje < 4; etasje++){
                    printf("\n");
                    for (int i = 0; i < 2; i++){
                        printf("\t%i", orders[etasje][i]);
                    }
                }
                printf("\n");

    if(currDir != 0) {


    	for (int floor = (currFloor + currDir); (floor < N_FLOORS) && (floor >= 0); floor += currDir) {
        	
            if (orders[floor][0] || orders[floor][1] ) {
                //printf("Etasjeorde i currDir retning = %i \n", *orders[floor][0] + *orders[floor][1]);
                

                
            		//15printf("RETURNED currDir.\n");
                    debugger(15, prevDebug);
                    printf("currDir_1 = %i \n",currDir);
            		return currDir;
            	}
        }
    
         
    	if (floorAllignment) {
        	for (int floor = (currFloor - currDir); (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            	if (orders[floor][0] || orders[floor][1] ) {
                	//16printf("RETURNED -currDir.\n");
                     debugger(16, prevDebug);
                     printf("currDir_2 = -%i \n",currDir);
                	return -currDir;
            	}
        	}
        	//17printf("RETURNED 0.\n");
            debugger(17, prevDebug);
        	return 0;
    	} else { //If not alligned with floor /////wut=**********************************************************
        	printf("Hallo  -------------  getDir - ikke floorAllignment");
        	for (int floor = currFloor ; (floor < N_FLOORS) && (floor >= 0); floor -= currDir) {
            		if (orders[floor][0] || orders[floor][1] ) {
                	   //18printf("RETURNED -currDir.\n");
                        debugger(18, prevDebug);
                        printf("currDir_3 = -%i \n",currDir);
                	return -currDir;
            		}
        	}
        }
    }

        for (int floor = currFloor + currDir; (floor < N_FLOORS) && (floor >= 0); floor++) {
            	if (orders[floor][0] || orders[floor][1] ) {
                	//19printf("RETURNED 1.\n");
                    debugger(19, prevDebug);
                    printf("currDir_4 = %i \n",1);
                	return 1;
                }
        }
        for (int floor = currFloor; (floor < N_FLOORS) && (floor >= 0); floor--) {
            	if (orders[floor][0] || orders[floor][1] ) {
                	//20printf("RETURNED 0.\n");
                    debugger(20, prevDebug);
                    printf("currDir_5 = %i \n", -1);
                	return -1;       
    			}
    	}
    
    //21printf("------>  Ended up returning 0 \n");
    debugger(21, prevDebug);    
    return 0;
} //getDir

int checkOrder(int orders[4][2], int elevParam[], int* prevDebug) {

   		//22printf("          Called checkOrder().\n");
        debugger(22, prevDebug);  
    	int currFloor = elevParam[0]; 
		int currDir = elevParam[2];

        if (currDir == 1 && orders[currFloor][0]) {
            //23printf("RETURNED 1.\n");
            debugger(23, prevDebug);
            return 1;
    }
                   
        if (currDir == -1 && orders[currFloor][1]) {
            //24printf("RETURNED 1.\n");
            debugger(24, prevDebug);
            return 1;
    }
        
        if (currDir == 0 && (orders[currFloor][1] || orders[currFloor][0])) {
            //25printf("RETURNED 1.\n");
            debugger(25, prevDebug);
            return 1;
    }
        
        //26printf("RETURNED 0.\n")
        debugger(26, prevDebug);
        return 0;
} //checkOrder


void deleteOrder(int orders[4][2], int floor, int* prevDebug){

        	//27printf("          Called deleteOrder().\n");
            debugger(27, prevDebug);
    
 			orders[floor][0] = 0;
 			orders[floor][1] = 0;

            elev_set_button_lamp(2, floor, 0);

            if (!(floor == 0)){
                elev_set_button_lamp(1 , floor, 0);
            }
            if (!(floor == 3)){
                elev_set_button_lamp(0 , floor, 0);
            }
            
            
} //deleteOrder

void newOrder(int orders[4][2], int floor, int type, int* prevDebug){

        printf("*** Følgende ordre legges i kø: %i etasje, %i retning.\n", floor, type);

       		//28printf("          Called newOrder() for ");
            debugger(28, prevDebug);
        
        

		if (floor == 0) {
		//29printf("1st floor.\n");
        debugger(29, prevDebug);
		}
		else if (floor == 1) {
		//30printf("2nd floor.\n");
        debugger(30, prevDebug);
		}
		else if (floor == 2) {
		//31printf("3rd floor.\n");
        debugger(31, prevDebug);
		}	
		else if (floor == 3) {
		//32printf("4th floor.\n");
        debugger(32, prevDebug);
		}			

        elev_set_button_lamp(type, floor, 1);


		if (type == 2) {
        orders[floor][0] = 1;
		orders[floor][1] = 1;
		} else {
		orders[floor][type] = 1;
		}
        printf("----> HAR LAGT INN ORDRE <----\n");

} //newOrder


        
            
            
