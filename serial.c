
#include <stdio.h>
#include <termios.h>    // POSIX terminal control definitions
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048
#define UART_SPEED B1152000

int main(void) {
    int fd;
    unsigned char   dev_UART_TOUCH[] = "/dev/ttyACM5";
    unsigned char rx_buffer[BUFFER_SIZE];
    int res;
    int ct=0;
    struct termios uart_settings;

    fd = open(dev_UART_TOUCH, O_RDWR);      //讀寫模式開啟
    if (fd==-1)
    {
        printf("Error opening\n");
        return -1;
    }
    else
    {
        printf("sucess opening\n");
    }
    //用來取得目前的串列埠參數值。
    tcgetattr(fd, &uart_settings);

    //=========================輸入模式===============================
    // 串列埠忽略同位錯誤，接收傳入的字元
    uart_settings.c_iflag = IGNPAR;
    //================================================================


    //=========================輸出模式===============================
    //若要啟動輸出處理，必須加入OPOST選項，程式碼如下：
    //options.c_oflag |= OPOST;
    //將換列字元轉換成[CR][LF]
    //options.c_oflag |= OPOST | ONLCR;
    //若要啟動非正規模式，將OPOST選項設為disable，設定如下：
    uart_settings.c_oflag &= ~OPOST;
    //================================================================


    //=========================控制模式===============================
    // 將波特率設定為115200bps。
    uart_settings.c_cflag = UART_SPEED | CLOCAL | CREAD;
    
    // 設定(8N1)傳輸資料長度8位元、無同位元檢查、1停止位元：
    uart_settings.c_cflag |= ~PARENB;     //不允許同位元檢查
    uart_settings.c_cflag |= ~CSTOPB;     //不是2停止位元
    uart_settings.c_cflag |= CS8;             //8 bits

    //將串列埠設定為正規模式
    uart_settings.c_lflag |= (ICANON | ECHO | ECHOE);
    //================================================================

    
    
    //=========================特殊控制字元============================
    // 組合                 說明
    // MIN=0, TIME = 0      以read()函數讀取串列埠後立即返回，若讀取到字元則傳回字元，否則傳回0。
    // MIN=0, TIME > 0      以read()函數讀取串列埠後，會在TIME時間內等待第一個字元。若有字元傳入或時間到，立即返回。若讀取到字元則傳回字元，否則傳回0。
    // MIN > 0, TIME = 0	以read()函數讀取串列埠後會等待資料傳入，若有MIN個字元可讀取，傳回讀取的字元數。
    // MIN > 0, TIME > 0	以read()函數讀取串列埠後，會等待資料的傳入。若有MIN個字元可讀取時，傳回讀取到的字元數。若TIME的時間到，則read()傳回0。
    uart_settings.c_cc[VTIME] = 0;
    uart_settings.c_cc[VMIN] = 0;
    //================================================================


    cfsetispeed(&uart_settings,UART_SPEED);   //傳回串列埠的輸入速率
    cfsetospeed(&uart_settings,UART_SPEED);   //設定串列埠的輸入速度

    // 執行後使用fp指向的termios資料結構，重新設定檔案描述子fd，其中引數action可以是下列的值
    // action值         說明
    // TCSANOW          立即將值改變
    // TCSADRAIN        當目前輸出完成時，將值改變
    // TCSAFLUSH        當目前輸出完成時，將值改變；並捨棄目前所有的輸入。
    tcsetattr(fd, TCSANOW, &uart_settings);

    // 清除所有佇列在串列埠的輸入和輸出。    
    // queue值      說明
    // TCIFLUSH     清除輸入
    // TCOFLUSH     清除輸出
    // TCIOFLUSH    清除輸入和輸出
	tcflush(fd, TCIFLUSH);
    
    printf("start print\n");
    
    while(1){
        res = read(fd, rx_buffer, BUFFER_SIZE);
        //printf("res[%04d]\n", res);
        rx_buffer[res] = 0;
        printf("res=%d buf=%s\n", res, rx_buffer);
        if (rx_buffer[0] == '@') break;
    }

    close(fd);
    return 0;
}