
#include "elev.h"
#include <stdio.h>
#include "eventmanager.h"
#include "fsm.h"
#include <time.h>


int eventManager() {

    state_t currState = INITIALIZE;

    int msec = 0, trigger = 300, delayIsActive = 0, delayRequest = 0; //Event manager holds the timer-function of the elevator. 
    clock_t startTime;    
    
    int orders[N_FLOORS][2];

    for (int i = 0; i < N_FLOORS; i++){
                for (int j = 0; j < 2; j++){
                    orders[i][j] = 0;
                }
    }

    int elevParam[4] = {0, 0, -1, 0}; //List to hold the parameters of the elevator (current floor, alligned with floor, current direction, last "secure" direction used in STOP evetn).

    elev_set_motor_direction(DIRN_DOWN); //Initialize state.

    while(!elev_get_obstruction_signal()) {

		
                //Stop event has prioritation over the other events. It calls the state machine with a stop event, delayrequest is added 1 if the timer is required.          
    		if (elev_get_stop_signal()){
                    			delayRequest += newEvent( 1, 0, 0, 0, 0, 0, orders, &currState, elevParam); 
    		} 

                else { //No stop event. 

		int floorSensorSignal = elev_get_floor_sensor_signal();
        		
                if (floorSensorSignal != -1) {

			delayRequest += newEvent( 0, floorSensorSignal+1, 0, 0, 0, 0, orders, &currState, elevParam); //The floor event is passed with +1 so it can easily be detected in the state machine.

        	}//End of floor sensor poll.
        		
               	for (int buttonPollType = 0; buttonPollType < 3; buttonPollType++){
    			for (int buttonPollFloor = 0; buttonPollFloor < N_FLOORS; buttonPollFloor++){
    				if (!((buttonPollFloor == 0 && buttonPollType == 1) || (buttonPollFloor == 3 && buttonPollType == 0)) && elev_get_button_signal(buttonPollType, buttonPollFloor)){ //Polls the buttons on the elevator, avoids undefined buttons (down from 1st floor etc).
					delayRequest += newEvent( 0, 0, 1, buttonPollType, buttonPollFloor, 0, orders, &currState, elevParam);
    				}
    			}
    		} //End of button polling.
            
            }//End of no stop signal procedure.

            if (delayRequest || delayIsActive) { //Timer function being called if timer is active (delayIsActive) or requested (delayRequest). 

                if (delayRequest) {
                    startTime = clock();
                    delayIsActive = 1;
                    delayRequest = 0;
                }

                clock_t timeDifference = clock() - startTime;
                msec = timeDifference * 1000 / CLOCKS_PER_SEC;

                if (msec >= trigger) {
                    delayIsActive = 0;
                    delayRequest = newEvent(0, 0, 0, 0, 0, 1, orders, &currState, elevParam); //When timer reaches the trigger it passes a delay event to the state machine. 
                }
            } //End of timer procedure. 



            
			
    } //End of while !elev_get_obstruction_signal() procedure.

    return 0;
}


