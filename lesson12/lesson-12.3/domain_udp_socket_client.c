/* 
lesson 12-3 
file name: domain_udp_socket_client, 
this file is part of a program that illustrates the usage of Datgram Domain Sockets

 Description
 -----------
 The program requires 2 files:
 domain_udp_socket_server 
 domain_udp_socket_client (THIS ONE)
 
 the Client side creates a Domain socket and starts wrting to the server
 loop-back (127.0.0.1) is used for Internet Addressing 
 the server part should run before the client
  
   
	
To compile me for Linux, use gcc -ggdb domain_udp_socket_client.c -o udp_socket_client 
To execute, type:  ./udp_socket_client
*/ 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
int sock;
struct sockaddr_in server_addr;
struct hostent *host;
char send_data[1024];

host= (struct hostent *) gethostbyname((char *)"127.0.0.1");


if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
perror("socket");
exit(1);
}

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(5000);
server_addr.sin_addr = *((struct in_addr *)host->h_addr);
bzero(&(server_addr.sin_zero),8);

   while (1)
   {

    printf("Type Something (q or Q to quit):");
    gets(send_data);

    if ((strcmp(send_data , "q") == 0) || strcmp(send_data , "Q") == 0)
       break;

    else
       sendto(sock, send_data, strlen(send_data), 0,
              (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
     
   }

}
