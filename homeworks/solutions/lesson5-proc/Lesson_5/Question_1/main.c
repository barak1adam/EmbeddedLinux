/*
Code making the following
1. Creates child process
2. Prints pid and ppid in each process
3. Add sleep(2) to the parent process, and endless loop to the child process. What happens?
Answer: If there is an endless loop in the child process and the parent process didn't call wait,
         then the parent process terminates before the child process and this is BAD, 
         since there isn't a process to clean up after the child process.

4. How to pass information from parent process to child process?
Answer: We can use IPC for sending information between parent-child processe.
*/

#include <stdio.h>      // IO operations
#include <unistd.h>   	//for pid, ppid, fork functions
#include <sys/types.h>  //for pid_t type, kill function
#include <stdlib.h> 	//for exit function
#include <signal.h>	//for kill function

int main ()
{
	pid_t pid = fork();
	
	if (0 == pid) //child process
	{
		int i = 0;
//		for (i=0;i<100000;i++)
		for (;;)
			printf ("I'm the child process: pid=%d, ppid=%d\n", getpid(), getppid());
	}
	else if (pid < 0)//fork failed
	{
		perror ("Fork failed");
		exit (1);
	}
	else // parent process
	{
		printf ("I'm the parent process: pid=%d, ppid=%d\n", getpid(), getppid());
		sleep(1);
		//4.printf ("PARENT: finished sleeping, now kill the child process");
		//4.kill(pid, 9);
	}
	return 0;
}
