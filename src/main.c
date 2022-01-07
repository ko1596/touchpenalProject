#include "displayLCD.h"
#include "gstService.h"
#include "serialService.h"

int main() {
    initGST();
    pthread_create(&serialThread, NULL, UartLoop, NULL);

    PageStatus = 2;
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

    
    generateFrame();
    displayScreen();

    while(1){
        // printf("%d\n", block[10]);
        if(block[10] < 50000 && block[10] > 5000){
            if(parkingTime > 0) parkingTime--;
            timeButtons = 1;
            generateFrame();
            usleep(100);
            displayScreen();
        }
        else if(block[11] < 50000 && block[11] > 5000){
            parkingTime++;
            timeButtons = 2;
            generateFrame();
            usleep(100);
            displayScreen();
        }
        else if(block[17] < 50000 && block[17] > 5000){
            selectButton = 1;
            generateFrame();
            usleep(100);
            displayScreen();
        }
        else if(block[18] < 50000 && block[18] > 5000){
            selectButton = 2;
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