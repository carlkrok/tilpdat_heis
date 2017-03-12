
#pragma once

int getDir(int orders[4][2], int elevParam[], int* prevDebug);
int checkOrder(int orders[4][2], int elevParam[], int* prevDebug);
void deleteOrder(int orders[4][2], int floor, int* prevDebug);
void newOrder(int orders[4][2], int floor, int dir, int* prevDebug);





