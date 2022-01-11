#include <unistd.h>

#include "displayLCD.h"
#include "gstService.h"

void processCommand(int);
void display();

int main() {
    int input;

    initGST();
    initData();

    display();
    while(1) { 
        printf("請輸入數字：");
        scanf("%d", &input);

        processCommand(input);
    }


    sleep(6);
    freeResources();
    return 0;
}

void processCommand(int command) {
    switch (pageStatus)
    {
    case PAGE_HOMEPAGE:
        if(command == 3 || command == 4) pageStatus = PAGE_BLOCK_SELECT_PAGE;
        else if(command == 9) pageStatus = PAGE_FREE_PARKING_PAGE;
        else if(command == 10) pageStatus = PAGE_NO_PARKING_PAGE;
        else if(command == 11) pageStatus = PAGE_Blank_PAGE;
        break;

    case PAGE_BLOCK_SELECT_PAGE:
        if(command == 3) {
            selectBlockLR = 1;
            display();
            
            pageStatus = PAGE_PAYMENT_PAGE;
        }
        else if(command == 4) {
            selectBlockLR = 2;
            display();
            
            pageStatus = PAGE_PAYMENT_PAGE;
        }
        else if(command == 12) {
            leftHaveCar = 1;
            BlockDataLeft.timeHour = 0;
            BlockDataLeft.timeMinute = 3;
            BlockDataLeft.blockStatus = BLOCK_PAYMENT;

            BlockDataLeft.stopTimeMonth = 1;
            BlockDataLeft.stopTimeDay = 12;
            BlockDataLeft.stopTimeHour = 6;
            BlockDataLeft.stopTimeMinute = 5;
        }
        else if(command == 13) {
            rightHaveCar = 1;
            BlockDataRight.timeHour = 0;
            BlockDataRight.timeMinute = 5;
            BlockDataRight.blockStatus = BLOCK_PAYMENT;

            BlockDataRight.stopTimeMonth = 1;
            BlockDataRight.stopTimeDay = 12;
            BlockDataRight.stopTimeHour = 7;
            BlockDataRight.stopTimeMinute = 8;
        }
        else if(command == 14) {
            leftHaveCar = 0;
            BlockDataLeft.timeHour = 99;
            BlockDataLeft.timeMinute = 99;

            BlockDataLeft.blockStatus = BLOCK_EMPTY;

            BlockDataLeft.stopTimeMonth = 99;
            BlockDataLeft.stopTimeDay = 99;
            BlockDataLeft.stopTimeHour = 99;
            BlockDataLeft.stopTimeMinute = 99;
        }
        else if(command == 15) {
            rightHaveCar = 0;
            BlockDataRight.timeHour = 99;
            BlockDataRight.timeMinute = 99;

            BlockDataRight.blockStatus = BLOCK_EMPTY;

            BlockDataRight.stopTimeMonth = 99;
            BlockDataRight.stopTimeDay = 99;
            BlockDataRight.stopTimeHour = 99;
            BlockDataRight.stopTimeMinute = 99;
        }
        
        break;

    case PAGE_PAYMENT_PAGE:
        if(command == 2) {
            pageStatus = PAGE_BLOCK_SELECT_PAGE;
            selectBlockLR = 0;
        }
        else if(command == 5) {
            pageStatus = PAGE_SUCCESS_PAGE;
            display();
            sleep(3);
            if(selectBlockLR == 1) { 
                BlockDataLeft.timeHour = 23;
                BlockDataLeft.timeMinute = 59;
                BlockDataLeft.blockStatus = BLOCK_DEADLINE;

                
            }else if(selectBlockLR == 2){ 
                BlockDataRight.timeHour = 23;
                BlockDataRight.timeMinute = 59;
                BlockDataRight.blockStatus = BLOCK_DEADLINE;
            }
            pageStatus = PAGE_BLOCK_SELECT_PAGE;
            selectBlockLR = 0;
        }
        else if(command == 6) {
            pageStatus = PAGE_PAYMENT_FAIL_PAGE;
            display();
            sleep(3);
            pageStatus = PAGE_BLOCK_SELECT_PAGE;
            selectBlockLR = 0;
        }
        else if(command == 7) {
            pageStatus = PAGE_PAYMENT_CONNECTION_PAGE;
            display();
            sleep(3);
            pageStatus = PAGE_BLOCK_SELECT_PAGE;
            selectBlockLR = 0;
        }
        else if(command == 8) {
            pageStatus = PAGE_CONNECTION_FAIL_PAGE;
            display();
            sleep(3);
            pageStatus = PAGE_BLOCK_SELECT_PAGE;
            selectBlockLR = 0;
        }
    
    default:
        break;
    }

    display();
}

void display() { 
    generateFrame();
    displayScreen();
}
