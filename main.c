
#include "elev.h"
#include <stdio.h>
#include "eventmanager.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    else {
    	printf("Initialization complete.\n");
    }
    
    eventManager();
    
    return 0;
}
