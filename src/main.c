#include "displayLCD.h"
#include "gstService.h"
#include "serialService.h"

int main() {
    initGST();
    pthread_create(&serialThread, NULL, UartLoop, NULL);

    PageStatus = 7;
    parkBK[0] = 1;
    parkBK[1] = 1;
    parkBK[2] = 0;
    parkBK[3] = 1;
    parkBK[4] = 1;
    parkBK[5] = 3;
    parkBK[6] = 2;
    parkBK[7] = 1;
    selectedBlock = 3;

    parkingTime = 5;
    parkingSpace = 16;
    timeButtons = 0;
    selectButton = 0;

    backButton = 0;

    
    generateFrame();
    displayScreen();

    while(1){
        
        if(block[17] < 50000 && block[17] > 5000){
            backButton = 1;
            generateFrame();
            usleep(100);
            displayScreen();
        }
        else if(block[18] < 50000 && block[18] > 5000){
            backButton = 1;
            generateFrame();
            usleep(100);
            displayScreen();
        }
        
        usleep(100);
    }

    sleep(6);
    freeResources();
    return 0;
}