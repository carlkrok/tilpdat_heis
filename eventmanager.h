
#pragma once

typedef enum {INITIALIZE, WAIT, DOOR_OPEN, TRANSPORTING } state_t; //Current state is initialized in event manager, but only used in the state machine wich takes the variable's adress as an argument. 


int eventManager(); //The event manager polls the parameters of the elevator and calls the state machine in case of events. 




