/* Includes */
#include "serial.h"
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */
 

/************************************************************************************
* communicating via serial line
* based on class exercise 4.4

* I would like to:
* 1. detect which serial port to open
* 2. use special characters instead of "BYE"
* 3. understand cannonical / non-canonical modes
* 4. use /dev/full

* how to test it:
=================
-connect my PC to PC or to OS.
-check that input on PC1 is output on PC1 and vice versa.
-check that upon "Bye", connection is stopped.

*************************************************************************************/
#include <termios.h>
#include <fcntl.h>
#include <string.h>

int func7()
{
	int fd;
	struct termios options;
	int n;
	char buff[255];

	/* Open Port - Detect which serial port to open
mrv@mrv-HP-Compaq-8000-Elite-Convertible-MT:~/os-v/router/vrrp$ dmesg | grep tty
[    0.000000] console [tty0] enabled
[    0.520388] 00:03: ttyS0 at I/O 0x3f8 (irq = 4, base_baud = 115200) is a 16550A
[    0.541991] 0000:00:03.3: ttyS4 at I/O 0x2248 (irq = 17, base_baud = 115200) is a 16550A
	*/
	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);  /* <--- YOUR PORT */
	
	if(fd == -1) {
		printf("ERROR Open Serial Port!");
		exit(-1);
	}

	/* Serial Configuration */
	tcgetattr(fd, &options);   // Get Current Config
	cfsetispeed(&options, B9600); // Set Baud Rate
	cfsetospeed(&options, B9600);
	options.c_cflag = (options.c_cflag & ~CSIZE) | CS8;
	options.c_iflag =  IGNBRK;
	options.c_lflag = 0;
	options.c_oflag = 0;
	options.c_cflag |= CLOCAL | CREAD;
	options.c_cc[VMIN] = 1;
	options.c_cc[VTIME] = 5;
	options.c_iflag &= ~(IXON|IXOFF|IXANY);
	options.c_cflag &= ~(PARENB | PARODD);

	/* Save The Configure */
	tcsetattr(fd, TCSANOW, &options);
	/* Flush the input (read) buffer */
	tcflush(fd,TCIOFLUSH);


	write(fd,"YOUR COMMAND STRING HERE",24);

	do{
		n = read(fd,buff,255);   // Read Data From Serial Port
		buff[n] = 0;
		if(n>0)
		{
			printf("%s",buff); // Print Out
		}
	}while(strncmp(buff,"bye",3)); // If user say bye then Exit

	close(fd); // Close Port
	return 0; // End Program
}


