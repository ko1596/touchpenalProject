#include "displayLCD.h"

void generateFrame(void)
{
	char buf[1024];
    char temp[1024];
    Block_Data_t bd;

    memset(buf, 0, sizeof(buf));
    memset(temp, 0, sizeof(temp));
    strcat(buf, WORK_SPACE_DIR);

    switch (pageStatus)
    {
    case PAGE_HOMEPAGE:
        strcat(buf, "0");
        break;

    case PAGE_BLOCK_SELECT_PAGE:
        sprintf(temp,"1 %02d:%02d %d %02d-%02d　%02d:%02d %s %02d:%02d %d %02d-%02d　%02d:%02d %s %d %d %d", 
                BlockDataLeft.timeHour,
                BlockDataLeft.timeMinute,
                BlockDataLeft.blockStatus,
                BlockDataLeft.stopTimeMonth,
                BlockDataLeft.stopTimeDay,
                BlockDataLeft.stopTimeHour,
                BlockDataLeft.stopTimeMinute,
                BlockDataLeft.blockName,

                BlockDataRight.timeHour,
                BlockDataRight.timeMinute,
                BlockDataRight.blockStatus,
                BlockDataRight.stopTimeMonth,
                BlockDataRight.stopTimeDay,
                BlockDataRight.stopTimeHour,
                BlockDataRight.stopTimeMinute,
                BlockDataRight.blockName,
                
                selectBlockLR,
                leftHaveCar,
                rightHaveCar);
        strcat(buf, temp);
        break;

    case PAGE_PAYMENT_PAGE:
        if(selectBlockLR == 1){ 
            bd = BlockDataLeft;
        }
        else if(selectBlockLR == 2){
            bd = BlockDataRight;
        }

        sprintf(temp,"2 %d %s %02d-%02d　%02d:%02d", 
                payment,
                bd.blockName,
                bd.stopTimeMonth,
                bd.stopTimeDay,
                bd.stopTimeHour,
                bd.stopTimeMinute );
        strcat(buf, temp);
        break;
    
    case PAGE_SUCCESS_PAGE:
        if(selectBlockLR == 1)
            bd = BlockDataLeft;
        else if(selectBlockLR == 2)
            bd = BlockDataRight;
        sprintf(temp, "3 %s", bd.blockName);
        strcat(buf, temp);
        break;

    case PAGE_PAYMENT_FAIL_PAGE:
        strcat(buf, "4");
        break;

    case PAGE_PAYMENT_CONNECTION_PAGE:
        strcat(buf, "5");
        break;

    case PAGE_CONNECTION_FAIL_PAGE:
        strcat(buf, "6");
        break;

    case PAGE_FREE_PARKING_PAGE:
        strcat(buf, "7");
        break;

    case PAGE_NO_PARKING_PAGE:
        strcat(buf, "8");
        break;

    case PAGE_Blank_PAGE:
        strcat(buf, "9");
        break;

    default:
        break;
    }

    printf("%s\n", buf);
    system(buf);
}

void initData(void) {

    pageStatus = PAGE_HOMEPAGE;
    payment = 10;

    BlockDataLeft.timeHour = 99;
    BlockDataLeft.timeMinute = 99;

    BlockDataLeft.blockStatus = BLOCK_EMPTY;

    BlockDataLeft.stopTimeMonth = 99;
    BlockDataLeft.stopTimeDay = 99;
    BlockDataLeft.stopTimeHour = 99;
    BlockDataLeft.stopTimeMinute = 99;

    sprintf(BlockDataLeft.blockName,"%s", "001");

    BlockDataRight.timeHour = 99;
    BlockDataRight.timeMinute = 99;

    BlockDataRight.blockStatus = BLOCK_EMPTY;

    BlockDataRight.stopTimeMonth = 99;
    BlockDataRight.stopTimeDay = 99;
    BlockDataRight.stopTimeHour = 99;
    BlockDataRight.stopTimeMinute = 99;

    sprintf(BlockDataRight.blockName,"%s", "002");

    selectBlockLR = 0;
    leftHaveCar = 0;
    rightHaveCar = 0;
}
