#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
int main(int argc, char *argv[])
{
   	int fd;
	FILE *fp;
	struct termios tty;
	unsigned char cmd[256];
	char rec[256];
	int  size=0;
	speed_t baudrate;
//	if(argc!=2)
//	{
//		printf("Input incorrect!\n");
//		return -1;
//	}
	fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY | O_NONBLOCK);

	if(fd == -1)
	{
			printf("Error! in Opening %s\n",argv[2]);
			return -1;
	}
	baudrate=B9600;
	memset (&tty, 0, sizeof tty);

	/* Error Handling */
	if ( tcgetattr ( fd, &tty ) != 0 ) {
	   printf("tcgetattr error\n");
	}

	/* Set Baud Rate */
	cfsetospeed (&tty, baudrate);
	cfsetispeed (&tty, baudrate);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  0;                  
	tty.c_cc[VTIME]  =  0;                  
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);
	/* Flush Port, then applies attributes */
	tcflush( fd, TCIFLUSH );

	if ( tcsetattr ( fd, TCSANOW, &tty ) != 0) {
	   printf("tcsetattr error\n");
	}

//	while(1) {
		char s1[20];
		printf("input: ");
		scanf("%s",s1);
		size=write(fd,s1,strlen(s1));
		printf("send : ");
		for(int i=0;i<strlen(s1);i++)
			printf("%d, ",s1[i]);
		printf("\n");
		for(int i=0;i<5000;i++)
		{
			usleep(1000);
			size=read(fd,cmd,256);
			if(size>0)
			{
				//printf("Took %d ms and read %d bytes: ",i,size);
				printf("rescv : ");
				for(int j=0;j<size;j++)
					printf("%d,",cmd[j]);
				printf("\n");
				break;
//				close(fd);
//				return 0;
			}
		}	
//	}

	printf("timeout!!\n");
	close(fd);
	return -1;
}
