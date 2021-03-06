/* lesson 13-1 file local_socket_server, this file is part of a program that illustrates the usage of Local Sockets

 Description
 -----------
 The program requires 2 files:
 local_socket_server (THIS ONE)
 local_socket_client 
 
 the Server side creates a local socket and writes to it
 the server part should run before the client
  
   
	
To compile me for Linux, use gcc -ggdb local_socket_server.c -o local_socket_server 
To execute, type:  ./local_socket_server
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

//prototype
int server (int new_socket);


/****************************************************************************************************/
int main (int argc, char* const argv[])
{
//const char* const socket_name = argv[1];
  const char* const socket_name = "my_socket";
  int socket_fd;
  struct sockaddr_un name;
  int client_sent_quit_message;
  
  /* Create the socket. */
  socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
  printf("server: socket_fd = %d.\n",socket_fd);
  
  /* Indicate that this is a server. */
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_path, socket_name);
  
  bind (socket_fd, (struct sockaddr *)&name, SUN_LEN (&name));
  
  /* Listen for connections. */
  listen (socket_fd, 5);
  /* Repeatedly accept connections, spinning off one server() to deal
     with each client. Continue until a client sends a "quit" message.   */
  do {
        struct sockaddr_un client_name;
        socklen_t client_name_len;
        int new_socket_fd;
  
        /* Accept a connection. */
        new_socket_fd = accept (socket_fd, (struct sockaddr *)&client_name, &client_name_len);
        printf("server: bind created new_socket_fd = %d \n",new_socket_fd);   
        
         /* Handle the connection. */
        client_sent_quit_message = server (new_socket_fd);
      
         /* Close our end of the connection. */
        close (new_socket_fd);
  }
  while (!client_sent_quit_message);
  
  /* Remove the socket file.  */
  close (socket_fd);
  
  unlink (socket_name);
  
  return 0;
}
/*********************************************************/
int server (int new_socket)
{
int should_quit=0;
  while (1) {
    int length;
    char* text;
    /* First, read the length of the text message from the socket. If
       read returns zero, the client closed the connection. */
    if (read (new_socket, &length, sizeof (length)) == 0)
      return 0;
    /* Allocate a buffer to hold the text. */
    text = (char*) malloc (length);
    /* Read the text itself, and print it. */
    read (new_socket, text, length);
    printf ("%s\n", text);
    should_quit = strcmp (text, "quit");
    /* Free the buffer. */
    free (text);
    /* If the client sent the message "quit," we’re all done.  */
   
   //printf ("should_quit = %d\n", should_quit); 
   if (should_quit)
	return 0; //no
    else
      return 1;  //yes
  }
}