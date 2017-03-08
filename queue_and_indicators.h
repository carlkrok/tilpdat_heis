
#pragma once

int getDir(int (*orders)[4][2], int (*elevParam)[3]);
int checkOrder(int (*orders)[4][2], int (*elevParam)[3]);
void deleteOrder(int (*orders)[4][2], int floor);
void newOrder(int (*orders)[4][2], int floor, int dir);





