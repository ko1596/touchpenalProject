
#include "serialService.h"

struct Node
{
	unsigned char data;
	struct Node *next;
};

typedef struct Node Queue_Node;
Queue_Node *front = NULL;
Queue_Node *tail = NULL;
int size = 0;

#define BUFFER_SIZE 2048
#define UART_SPEED B1152000

void push(unsigned char a)
{
	Queue_Node *new_add_node;
	new_add_node = (Queue_Node *)malloc(sizeof(struct Node));
	
	new_add_node->data = a;
	new_add_node->next = NULL;

	if (tail == NULL||front==NULL)
	{
		front = new_add_node;
	}		
	else
		tail->next = new_add_node;
	
	
	tail = new_add_node;
}

unsigned char pop()
{
	Queue_Node *pt = front;
	unsigned char i = front->data;
	front = front->next;
	free(pt);
	return i;
}

int set_interface_attribs(int fd, int speed, int parity)
{
	struct termios tty;
	if (tcgetattr(fd, &tty) != 0)
	{
		return 1;
	}

	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK; // disable break processing
	tty.c_lflag = 0;		// no signaling chars, no echo,
							// no canonical processing
	tty.c_oflag = 0;		// no remapping, no delays
	tty.c_cc[VMIN] = 0;		// read doesn't block
	tty.c_cc[VTIME] = 5;	// 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
									   // enable reading
	tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	// tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		return 1;
	}
	return 0;
}

int set_blocking(int fd, int should_block)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if (tcgetattr(fd, &tty) != 0)
		return 1;

	tty.c_cc[VMIN] = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
		return 1;
}

int main(void)
{
	int fd;
	unsigned char dev_UART_TOUCH[] = "/dev/ttyACM0";
	unsigned char rx_buffer[BUFFER_SIZE];
	int res;
	int ct = 0;
	struct termios uart_settings;
	u_int8_t dataCommand;
	int commandState = 0;
	int count = 0;
	u_int16_t block[24];
	int blockCount = 0;
	int displayed = 0;
	int displayLock = 1;
	pthread_t t; // 宣告 pthread 變數
	initLCD();

	fd = open(dev_UART_TOUCH, O_RDWR); //讀寫模式開啟
	if (fd < 0)
	{
		printf("Can't open device %s.\n", dev_UART_TOUCH);
		return 1;
	}

	set_interface_attribs(fd, B115200, 0); // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking(fd, 0);				   // set no blockin

	usleep((7 + 25) * 100); // sleep enough to transmit the 7 plus
							// receive 25:  approx 100 uS per char transmit

	while (1)
	{
		res = read(fd, rx_buffer, BUFFER_SIZE);
		if (res > 0)
		{
			for (int i = 0; i < res; i++)
			{
				push(rx_buffer[i]);
				
			}
		}
		

		while (front != NULL)
		{
			dataCommand = pop();
			switch (commandState)
			{
				case 0:
					if(dataCommand == 0x12)
					{
						commandState = 1;
						displayed = 1;
						// usleep(500000); //  	0.5s
						// system("clear"); //*nix
					}
					break;
				case 1:
					if(dataCommand == 0x34)
					{
						commandState = 2;
					}
					break;
				case 2:
					
					// if(count%12 == 0) printf("\n");
					

					if(count%2 == 0)
					{
						block[blockCount] = dataCommand;
					}						
					else
					{
						block[blockCount] |= (dataCommand << 8);
						// printf("[%2d] %5u\t", blockCount, block[blockCount]);
						blockCount++;
					}

					count++;
					if(count == 48)
					{
						count = 0;
						commandState = 0;
						blockCount = 0;
					}
					
					break;

				default:
					break;
			}

		}
		// printf("displayed %d lock %d\n",displayed,lock);
		if(displayed&&lock)
		{
			lock = 0;
			pthread_create(&t, NULL, (void *)&displayFrame, (void *)&block[0]);
		}
			
		
	}

	close(fd);
	return 0;
}