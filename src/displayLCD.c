#include "displayLCD.h"

void generateFrame(void)
{
	char buf[1024];
    char temp[1024];

    memset(buf, 0, sizeof(buf));
    memset(temp, 0, sizeof(temp));
    strcat(buf, WORK_SPACE_DIR);

    switch (PageStatus)
    {
    case 0:
        strcat(buf, "0");
        break;

    case 1:
        strcat(buf, "1");
        sprintf(temp, " %d", selectedBlock);
        strcat(buf, temp);
        for (int i = 0; i < 8; i++){
            sprintf(temp, " %d", parkBK[i]);
            strcat(buf, temp);
        }
        strcat(buf," 5");
        break;

    case 2:
        strcat(buf, "2");
        sprintf(temp, " %d", parkingTime);
        strcat(buf, temp);
        sprintf(temp, " %d", parkingSpace);
        strcat(buf, temp);
        sprintf(temp, " %d", timeButtons);
        strcat(buf, temp);
        sprintf(temp, " %d", selectButton);
        strcat(buf, temp);
        break;

    case 7:
        strcat(buf, "7");
        sprintf(temp, " %d", parkingTime);
        strcat(buf, temp);
        sprintf(temp, " %d", parkingSpace);
        strcat(buf, temp);
        sprintf(temp, " %d", backButton);
        strcat(buf, temp);
    
    default:
        break;
    }

    printf("%s\n", buf);
    system(buf);
}


