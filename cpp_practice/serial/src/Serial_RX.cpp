#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define BAUDRATE B9600
#define _POSIX_SOURCE 1

int main(void)
{
	int fd,res,c=0;
	struct termios oldtio,newtio;
	char buf[256];
	char MODEDEVICE[30]="/dev/";
	char device[20];
	
	printf("Enter connect tty name:  ");
	scanf("%s",device);
	strcat(MODEDEVICE,device);
	
	printf("Reading %s ...\n",MODEDEVICE);
	printf("Start...\n");
	fd=open(MODEDEVICE,O_RDWR|O_NOCTTY);	//just read and write tty, avoid Ctrl+C to kill file

	if(fd<1)	//try open error 
	{
		perror(MODEDEVICE);
		exit(1);
	}
	else
	{
		printf("Open...\n");
	}
	
	tcgetattr(fd,&oldtio);
	memset(&newtio,0,sizeof(newtio));
	
	/*configure COM begin*/
	newtio.c_cflag=BAUDRATE|CS8|CLOCAL|CREAD;
	newtio.c_iflag=IGNPAR;
	newtio.c_oflag=0;
	newtio.c_lflag=ICANON;
	/*configure COM end*/

	tcflush(fd,TCIFLUSH);		//TCIFLUSH: clean serial input
	tcsetattr(fd,TCSANOW,&newtio);	//TCSANOW: change occurs immediately

	printf("Reading...\n");

	while(1)
	{
		res=read(fd,buf,255);
		buf[res]=0;
		printf("res=%d  buf=%s \n",res,buf);
		if(buf[0]=='@') break;
	}

	printf("Close...\n");
	close(fd);
	tcsetattr(fd,TCSANOW,&oldtio);
	return 0;
}
