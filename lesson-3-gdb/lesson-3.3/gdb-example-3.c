   // *****************
   // Demonstrates debugging a process
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 


   typedef unsigned short int USHORT;       //typedef defined

   int main()
   {
     USHORT  counter = 0;
	 pid_t pid = getpid(); 
     
	 while(1)
	 {
		  printf("counter: %d  %d\n",++counter,pid);
		  sleep(1);
	 }
	
     return 0;
 }

