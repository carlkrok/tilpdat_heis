
#ifndef eventmanager_h
#define eventmanager_h

enum state {INITIALIZE, WAIT, ELEVATOR_ACTIVATOR, DOOR_OPEN, STOP, TRANSPORTING };
int eventManager();

int orders[N_FLOORS][2] = {0};

/*
for (int i = 0; i < N_FLOORS; i++) {
  for (int j = 0; j < 2; j++){
    orders[i][j] = 0;
      }
}
*/

int fsmCurrFloor;
int fsmFloorAlignment;
int fsmCurrDir;

enum state currState = INITIALIZE;


#endif /* eventmanager_h */
