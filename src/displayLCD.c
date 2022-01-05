#include "displayLCD.h"

void generateFrame(void)
{
	char buf[1024];

    memset(buf, 0, sizeof(buf));
    strcat(buf, WORK_SPACE_DIR);

    switch (PageStatus)
    {
    case 0:
        strcat(buf, "0");
        break;

    case 1:
        strcat(buf, "1");
        for (int i = 0; i < 8; i++){
            strcat(buf,parkBK[i]);
        }
    
    default:
        break;
    }

    printf("%s\n", buf);
    system(buf);
}


