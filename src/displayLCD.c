#include "displayLCD.h"

void generateFrame(void)
{
	char buf[1024];
    char temp[1024];

    memset(buf, 0, sizeof(buf));
    memset(temp, 0, sizeof(temp));
    strcat(buf, WORK_SPACE_DIR);


    printf("%s\n", buf);
    system(buf);
}


