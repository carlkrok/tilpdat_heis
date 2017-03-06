
#ifndef queue_and_indicators_h
#define queue_and_indicators_h

int getDir(int currDir,int currFloor, int floorAllignement);
int checkOrder(int currFloor,int currDir);
void deleteOrder(int floor);
void newOrder(int floor, int dir);
int UP = 1;
int DOWN = 0;




#endif /* queue_and_indicators_h */
