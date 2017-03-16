
#pragma once


//The getDir function ignores the floor the elevator is on, and returns the direction in wich there is an order (the current direction is prioritized). The function returns 0 if there are no orders. 
int getDir(int orders[4][2], int elevParam[]);

//The checkOrder function checks if there are any orders on the floor the elevator is currently on. It returns 1 if there is an order, 0 otherwise. 
int checkOrder(int orders[4][2], int elevParam[]);

//Deletes all orders on the floor sent as an argument. 
void deleteOrder(int orders[4][2], int floor);

//Inserts the order given with orderFloor and orderDir in the matrix orders[][].
void newOrder(int orders[4][2], int orderFloor, int orderDdir);





