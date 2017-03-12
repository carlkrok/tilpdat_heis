
#include "elev.h"
#include <stdio.h>
#include "eventmanager.h"
#include "fsm.h"
#include <time.h>

state_t currState;

void debugger(int debugTall, int* prevDebug){
    
    if (debugTall != *prevDebug){
        int tall = debugTall;
        *prevDebug = debugTall;
        //*prevDebug = debugTall;

        //char printDebugCode[4] = {debugTall, tall, '\n', '\0'};
        //printf(&printDebugCode);

        
        if (tall == 1){
        //printf("******** Current state is: ");
        //printf(&state_names[this_state]);

        }
        else if (tall == 2){
            printf("   Stop event received in FSM.\n"); 
        }
        else if (tall == 3){
            printf("   Floor event received in FSM.\n");
        }
        else if (tall == 4){
            printf("   Button event received in FSM.\n");
        }
        else if (tall == 5){
            printf("--> Initialize state does nothing with button events.\n");
        }
        else if (tall == 6){
            printf("--> Calling newOrder from WAIT state.\n");
        }
        else if (tall == 7){
            printf("--> Calling newOrder.\n");
        }
        else if (tall == 8){
            printf("   Delay event received in FSM.\n");
        }
        else if (tall == 9){
            printf("        Reached delay finished event. \n");
        }
        else if (tall == 11){
            printf("Got a stop signal.\n");
        }
        else if (tall == 12){
            printf("Got a floor sensor signal.\n");
        }
        else if (tall == 13){
            printf("Got a button signal.\n");
        }
        else if (tall == 14){
            printf("          Called getDir().\n");
        }
        else if (tall == 15){
            printf("RETURNED currDir.\n");
        }
        else if (tall == 16){
            printf("RETURNED -currDir.\n");
        }
        else if (tall == 17){
            printf("RETURNED 0.\n");
        }
        else if (tall == 18){
            printf("RETURNED -currDir.\n");
        }
        else if (tall == 19){
            printf("RETURNED 1.\n");
        }
        else if (tall == 20){
            printf("RETURNED 0.\n");
        }
        else if (tall == 21){
            printf("------>  Ended up returning 0 \n");
        }
        else if (tall == 22){
            printf("          Called checkOrder().\n");
        }
        else if (tall == 23){
            printf("RETURNED 1.\n");
        }
        else  if (tall == 24){
            printf("RETURNED 1.\n");
        }
        else if (tall == 25){
            printf("RETURNED 1.\n");
        }
        else if (tall == 26){
            printf("RETURNED 0.\n");
        }
        else if (tall == 27){
            printf("          Called deleteOrder().\n");
        }
        else  if (tall == 28){
            printf("          Called newOrder() for ");
        }
        else if (tall == 29){
            printf("1st floor.\n");
        }
        else if (tall == 30){
            printf("2nd floor.\n");
        }
        else if (tall == 31){
            printf("3rd floor.\n");
        }
        else if (tall == 32){
            printf("4th floor.\n");
        }
        else if (tall == 33) {
            printf("----------------------\nReceived a delay request!\n");
        }
    }

}


int eventManager() {
    int msec = 0, trigger = 300, delayState = 0;
    clock_t startTime;

    int floorSensorSignal;
    int delayRequest = 0;

    state_t currState = INITIALIZE;

    printf("+++ State is now INITIALIZE. +++\n");
    
    int orders[N_FLOORS][2] = {{0,0},{0,0},{0,0},{0,0}};
     for (int etasje = 0; etasje < 4; etasje++){
                for (int i = 0; i < 2; i++){
                    orders[etasje][i] = 0;
                }
            }

    printf("Dette er  før start:");
    for (int etasje = 0; etasje < 4; etasje++){
                    printf("\n");
                    for (int i = 0; i < 2; i++){
                        printf("\t%i", orders[etasje][i]);
                    }
                }
                printf("\n");
    int elevParam[3] = {0, 0, -1};

    elev_set_motor_direction(-1); //Initialize driving.

    int prevDebug = 0;
    
    while(!elev_get_obstruction_signal()) {

            char state_names[8] = {'I', 'W', 'E', 'D', 'S', 'T', '\n', '\0'};
            int this_state = currState;
            //printf("******** Current state is:"); 
            //printf(&state_names[this_state]);
            
    		if (elev_get_stop_signal()){
                //11printf("Got a stop signal.\n");
                //debugger(11, &prevDebug);
    			delayRequest += newEvent( 1, 0, 0, 0, 0, 0, orders, &currState, elevParam, &prevDebug);
    		} //stopSignal

            else {
        		
                if ((floorSensorSignal = elev_get_floor_sensor_signal()) != -1) {
                    //12printf("Got a floor sensor signal.\n");
                    //debugger(12, &prevDebug);
                    delayRequest += newEvent( 0, floorSensorSignal, 0, 0, 0, 0, orders, &currState, elevParam, &prevDebug);
        		} //floorSensorSignal
        		
               	for (int buttonType = 0; buttonType < 3; buttonType++){
    				for (int floor = 0; floor < N_FLOORS; floor++){
    					if (!((floor == 0 && buttonType == 1) || (floor == 3 && buttonType == 0)) && elev_get_button_signal(buttonType, floor)){
    						//13printf("Got a button signal.\n");
                            //debugger(13, &prevDebug);
                            delayRequest += newEvent( 0, 0, 1, buttonType, floor, 0, orders, &currState, elevParam, &prevDebug);
    					}
    				}
    			} //buttonSignal
            
            }//If no stop signal

            if (delayRequest || delayState) {

		        //33printf("----------------------\nReceived a delay request!\n");
                //debugger(33, &prevDebug);

                if (delayRequest) {
                    startTime = clock();
                    delayState = 1;
                    printf("Starting timer.\n");
                    delayRequest = 0;
                }

                clock_t timeDifference = clock() - startTime;
                msec = timeDifference * 1000 / CLOCKS_PER_SEC;

                if (msec >= trigger) {
                    delayState = 0;
                    delayRequest = newEvent(0, 0, 0, 0, 0, 1, orders, &currState, elevParam, &prevDebug);
                    printf("----------------------\nTimer reached trigger.\n");
                }
            }



            
			
    } //while 1

    return 0;
}


