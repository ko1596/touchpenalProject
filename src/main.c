#include "displayLCD.h"
#include "gstService.h"

int main() {
    initGST();

    
    generateFrame();
    displayScreen();


    sleep(6);
    freeResources();
    return 0;
}