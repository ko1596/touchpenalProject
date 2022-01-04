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



	pthread_create(&displayThread, NULL, display, NULL); // 建立子執行緒
	// sleep(1);
	
	
	printf("thread end\n");
	
	lock = 1;
}

void initLCD() {
	lock = 1;
}

void *display(void *parm){
    char command[128];

    system("killall gst-launch-1.0");
    sprintf(command, "gst-launch-1.0 -q filesrc location=%sframe.png ! pngdec ! imagefreeze ! videoconvert ! video/x-raw, framerate=1/1 ! autovideosink", COMMAND_PATH);
    system(command);
    
    pthread_exit(NULL); // 離開子執行緒
}