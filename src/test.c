#include <stdlib.h>
#include <stdio.h>

#include "serialService.h"

int main(int argc, char *argv[]) {
    pthread_create(&serialThread, NULL, UartLoop, NULL);

    while(1){
        usleep(100000);
        system("clear");
        
        
        for(int i = 0; i < 24; i++){
            if(i%6 == 0) printf("\n");
            if(block[i] > 60000)
                printf("[%2d]00000\t",i);
            else
                printf("[%2d]%05u\t",i , block[i]);
            
        }
        
        
    }

    return 0;
}