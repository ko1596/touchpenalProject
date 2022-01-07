#include "displayLCD.h"
#include "gstService.h"
#include "serialService.h"

int main() {
    initGST();
    pthread_create(&serialThread, NULL, UartLoop, NULL);

    PageStatus = 1;
    parkBK[0] = 1;
    parkBK[1] = 1;
    parkBK[2] = 0;
    parkBK[3] = 1;
    parkBK[4] = 1;
    parkBK[5] = 3;
    parkBK[6] = 2;
    parkBK[7] = 1;
    selectedBlock = 3;
    generateFrame();
    displayScreen();

    while(1){
        for(int i = 0; i < 16; i++){
            if((block[i] < 50000) && (block[i] > 2000)){
                selectedBlock = i/2;
                generateFrame();
                displayScreen();
                
                
                break;
            }
        }
        usleep(100);
        
    }

    sleep(6);
    freeResources();
    return 0;
}