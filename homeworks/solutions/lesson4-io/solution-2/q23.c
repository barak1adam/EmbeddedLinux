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

#define ZERO_SD "/dev/zero"
#define FULL_SD "/dev/full"

int main(int argc, char *argv[])
{
  	int fd;
	size_t length = 1;
	char str[]="dddddddddddddddd";
	char buffer[80];

	buffer[0] = '\n';

	system("clear");
	//------------------------------------------q2---------------------------------------------
	//Open the Special device file /dev/zero, try reading from it

	fd = open(ZERO_SD, O_RDONLY);
	if (-1 == fd)
	{
		printf("Error to open ZERO_SD file \n");
		exit(-1);
	}

	length = read(fd, buffer, 79);
	printf("The length is %d \n", length);
	printf("The buffer is %s \n", buffer);

	close(fd);

	//------------------------------------------q3---------------------------------------------
	//Open the Special device file /dev/full, try writing to it

	fd = open(FULL_SD, O_RDWR);
	if (-1 == fd)
	{
		printf("Error to open FULL_SD file \n");
		exit(-1);
	}

	length = read(fd, buffer, 79);
	printf("The length is %d \n", length);
	printf("The buffer is %s \n", buffer);
	
	lseek(fd, 0, SEEK_END);
	length = write(fd, str, strlen(str));
	printf("The length is %d \n", length);
	if(-1 == length){
		printf("you can't write to FULL_SD even if you working with O_RDWR perm\n");}

	close(fd);

	
	
  	return EXIT_SUCCESS;
}
