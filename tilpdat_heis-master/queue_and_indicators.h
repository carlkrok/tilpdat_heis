
#pragma once

int getDir(int (*orders)[4][2], int currDir,int currFloor, int floorAllignement);
int checkOrder(int (*orders)[4][2], int currFloor,int currDir);
void deleteOrder(int (*orders)[4][2], int floor);
void newOrder(int (*orders)[4][2], int floor, int dir);





