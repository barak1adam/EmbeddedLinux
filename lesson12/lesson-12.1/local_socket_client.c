/* lesson 12-1 file local_socket_client, this file is part of a program that illustrates the usage of Local Sockets

 Description
 -----------
 The program requires 2 files:
 local_socket_server
 local_socket_client (THIS ONE)
 
 the client side creates a local socket and writes to it
 the client part should run after the server  
   
	
To compile me for Linux, use gcc -ggdb local_socket_client.c -o local_socket_client 

To execute, type:  ./local_socket_client  some_message_for_the_server
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

//prototype
void write_text (int socket_fd, const char* text);

/*************************************************************************/
int main (int argc, char* const argv[])
{
	const char* message=NULL;
	const char* const socket_name = "my_socket";
	int socket_fd;
	struct sockaddr_un name;
	
	if (argc>1)
	{
		message = argv[1];
	}
	else
	{
		message = "hello world";
	}
	
	
	/* Create the socket. */
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	printf("client: socket_fd = %d.\n",socket_fd);
	
	/* Store the server name in the socket address. */
	name.sun_family = AF_LOCAL;
	strcpy (name.sun_path, socket_name);
	
	/* Connect the socket. */
	connect (socket_fd, (struct sockaddr *)&name, SUN_LEN (&name));
	
	/* Write the text on the command line to the socket. */
	write_text (socket_fd, message);
	
	close (socket_fd);
	return 0;
}
/**************************************************************************/
/* Write TEXT to the socket given by file descriptor SOCKET_FD. */
void write_text (int socket_fd, const char* text)
{
/* Write the number of bytes in the string, including NUL-termination. */
	int length = strlen (text) + 1;
	write (socket_fd, &length, sizeof (length));

	/* Write the string. */
	write (socket_fd, text, length);
}
/**************************************************************************/

/* Remarks */
/*---------------------
/* the following are defined in Linux Kernel as:
/*
/*1.#define SUN_LEN(ptr) ((size_t) (((struct sockaddr_un *) 0)->sun_path)        \
/*                       + strlen ((ptr)->sun_path))
/*
/*2.#define UNIX_PATH_MAX   108
/*
/*3.typedef unsigned short  sa_family_t;
/*  
/*4.struct sockaddr_un {
/*           sa_family_t sun_family; /* AF_UNIX */
/*           char sun_path[UNIX_PATH_MAX];   /* pathname */
/*   };
/*
/*5./* Supported address families. */
/* #define AF_UNSPEC       0
/* #define AF_UNIX         1       /* Unix domain sockets          */
/* #define AF_LOCAL        1       /* POSIX name for AF_UNIX       */
/* #define AF_INET         2       /* Internet IP Protocol         */
 
 
