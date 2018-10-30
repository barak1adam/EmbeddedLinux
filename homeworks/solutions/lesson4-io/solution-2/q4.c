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


//Write a program that writes the environment variables into a created file named
//   environment in you home directory /home/$user_name .




int main(int argc, char *argv[], char *envp[])
{
  	
	
	char *pathname;
	int n, fd;

  	pathname = getenv ("PWD"); //cool function :)
	
  	
	strcat( pathname, "/environment.txt");

	if (pathname!=NULL)
    		printf ("The current path to file is: %s \n",pathname);
	else 	printf("Error with strcat");

	fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC , 0666);
	if (-1 == fd)
	{
		printf("Error to open file \n");
		exit(-1);
	}

	for (n=0; envp[n]; n++)
 	{
		lseek(fd, 0, SEEK_END);
		write(fd, envp[n], strlen(envp[n]));
		write(fd, "\n", 1);
	}
  

	close(fd);
  	return EXIT_SUCCESS;
}
