#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define BAUDRATE 9600
#define _POSIX_SOURCE 1
#define FIX_MODEDEVICE "/dev/ttyACM0"

int main(void)
{
	int fd,res,c=0;
	struct termios oldtio,newtio;
	char ch,te='w',hi[]="1";
	char s1[20];
	char MODEDEVICE[30]="/dev/";
	char device[20];

	/*printf("Enter connect tty name:  ");
	scanf("%s",device);
	strcat(MODEDEVICE,device);
	
	printf("Reading %s ...\n",MODEDEVICE);*/
	printf("Start...\n");
	fd=open(FIX_MODEDEVICE,O_RDWR|O_NOCTTY);
	printf("fd=%d", fd);
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
	newtio.c_oflag|=OPOST;
	newtio.c_lflag=ICANON;
	/*configure COM end*/

	tcflush(fd,TCOFLUSH);		//TCIFLUSH: clean serial input
	tcsetattr(fd,TCSANOW,&newtio);	//TCSANOW: change occurs immediately

	printf("Writting...\n");

	while(1)
	{
		scanf("%s",s1);
		ch=s1[0];
		//write(fd,&hi,3);
		//write(fd,&te,1);
		if(ch!='@')
		{
			printf("s1= %s\n",s1);
			//printf("s1[0]= %c\n",s1[0]);
			res=write(fd,s1,strlen(s1));
		}
		else
		{
			break;
		}
	}

	printf("Close...\n");
	close(fd);
	tcsetattr(fd,TCSANOW,&oldtio);
	return 0;
}
