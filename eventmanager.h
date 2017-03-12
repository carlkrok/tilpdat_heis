
#pragma once
typedef enum {INITIALIZE, WAIT, ELEVATOR_ACTIVATOR, DOOR_OPEN, STOP, TRANSPORTING } state_t;
int eventManager();
void debugger(int tall, int* oldCode);



/*
for (int i = 0; i < N_FLOORS; i++) {
  for (int j = 0; j < 2; j++){
    orders[i][j] = 0;
      }
}
*/




