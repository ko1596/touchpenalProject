#include "displayLCD.h"
#include "gstService.h"
// #include "serialService.h"

int main() {
    initGST();
    PageStatus = 0;

    generateFrame();
    displayScreen();
    sleep(6);
    freeResources();
    return 0;
}