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
    
    default:
        break;
    }

    // printf("%s\n", buf);
    system(buf);
}


