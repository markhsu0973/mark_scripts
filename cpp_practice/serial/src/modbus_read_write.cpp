#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

unsigned int crc_chk(unsigned char *data, unsigned char length)
{
	int j;
	unsigned int reg_crc = 0xFFFF;
	while (length--)
	{
		reg_crc ^= *data++;
		for (j = 0; j < 8; j++)
		{
			if (reg_crc & 0x01) /* LSB(b0)=1 */
				reg_crc = (reg_crc >> 1) ^ 0xA001;
			else
				reg_crc = reg_crc >> 1;
		}
	}
	return reg_crc;
}

void assignValue(unsigned char *cmd, unsigned char length, char *argv[])
{
	cmd[0] = strtol(argv[1], NULL, 10);
	cmd[1] = strtol(argv[2], NULL, 10);
	cmd[2] = strtol(argv[3], NULL, 10);
	cmd[3] = strtol(argv[4], NULL, 10);
	cmd[4] = strtol(argv[5], NULL, 10);
	cmd[5] = strtol(argv[6], NULL, 10);
	int crc_vlaue = crc_chk(cmd, 6);
	cmd[6] = crc_vlaue & 0xFF;
	cmd[7] = (crc_vlaue >> 8) & 0xFF;
	printf("crc_vlaue:%d\n", crc_vlaue);
	for (int j = 0; j < length + 2; j++)
		printf("cmd[%d]:%d,", j, cmd[j]);
	printf("\n");
}

int main(int argc, char *argv[])
{
   	int fd;
	FILE *fp;
	struct termios tty;
	unsigned char cmd[256];
	char rec[256];
	int  size=0;
	speed_t baudrate;
	if(argc!=7)
	{
		printf("Input incorrect!\n");
		return -1;
	}
	
	fd = open("/dev/compal_motor_driver",O_RDWR | O_NOCTTY | O_NONBLOCK);

	if(fd == -1)
	{
			printf("Error! in Opening %s\n",argv[2]);
			return -1;
	}
	baudrate=B115200;
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

	assignValue(cmd, 6, argv);

	size=write(fd,cmd,8);
	printf("send : ");
	for(int i=0;i<8;i++)
		printf("%d, ",cmd[i]);
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
			close(fd);
			return 0;
		}
	}
	printf("timeout!!\n");
	close(fd);
	return -1;
}
