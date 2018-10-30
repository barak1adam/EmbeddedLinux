/***************************************************************************
 *   Copyright (C) 2010 by root   *
 *   root@localhost.localdomain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <error.h>

int main(int argc, char *argv[])
{
  	int fd, fdnew;
	size_t length = 1;
	char re_buffer[80];
	char wr_buffer[] = "Hello World \n";

	re_buffer[0] = '\n';
	

	system("clear");
	system("pwd > RodionFile");
	
	//------------------------------------------1----------------------------------------------
	//Use the systems calls in order to read from /home/Rodion/Rodion via read only permissions

	fd = open("/home/Rodion/RodionFile",O_RDONLY);
	if (-1 == fd)
	{
		printf("Error to open this file \n");
		exit(-1);
	}

	length = read(fd, re_buffer, 80);
	printf("The length is %d \n", length);
	printf("The buffer is %s \n", re_buffer);

	//------------------------------------------2----------------------------------------------
	//Try to write to it (still with the same read only permissions
	length = write(fd, wr_buffer, strlen(wr_buffer));
	printf("The length is %d \n", length);
	
	printf("The file Content is: \n");
	system("cat RodionFile");
	if(-1 == length){
	printf("\nAs you see, we can't write to the file, because in this case, we use O_RDONLY \n");
	}

	close(fd);

	//------------------------------------------3-4--------------------------------------------
	//Try to opening the file with another fd and then write to it.

	fd = open("/home/Rodion/RodionFile",O_RDWR);
	if (-1 == fd)
	{
		printf("Error to open this file \n");
		exit(-1);
	}
	lseek(fd, 0, SEEK_END);
	length = write(fd, wr_buffer, strlen(wr_buffer));
	printf("The length is %d \n", length);
	
	printf("The file Content is: \n");
	system("cat RodionFile");

	close(fd);

	//------------------------------------------5----------------------------------------------
	//Create a file named a.txt within the program and copy the old file's content in it.
	fd = open("/home/Rodion/RodionFile",O_RDONLY);
	if (-1 == fd)
	{
		printf("Error to open this file \n");
		exit(-1);
	}

	fdnew = open("/home/Rodion/a.txt",O_RDWR | O_CREAT, 0666);
	if (-1 == fdnew)
	{
		printf("Error to open this file \n");
		exit(-1);
	}
	
	length = read(fd, re_buffer, 80);
	length = write(fdnew, re_buffer, length);

	printf("\n\nThe new file Content is: \n");
	system("cat a.txt");

	close(fd);
	close(fdnew);
	
  	return EXIT_SUCCESS;
}
