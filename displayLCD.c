#include "displayLCD.h"

void displayFrame(void *parm)
{
	u_int16_t *block = (u_int16_t*) parm; // 取得輸入資料
	
	printf("inthread\n");
	char path[1024] = "python3 frame.py";
	char convert[100];
	for (int i = 0; i < 24; i++)
	{
		sprintf(convert," %u", block[i]);
		strcat(path, convert);
	}

	
	printf("\n\n%s\n\n",path);
	system(path);
	
	printf("thread end\n");
	
	lock = 1;
}

void initLCD() {
	lock = 1;
}