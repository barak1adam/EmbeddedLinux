/* Listing 6.6 ( cancel-thread2.c) trying to terminate an Un-cancelable thread

Description
-----------
In this program main tries to terminate the newly created thread which is configured as PTHREAD_CANCEL_DISABLE,

Note: when compiling and link this program be sure to add the -lpthread library:
as the following:

% gcc cancel-thread2.c -lpthread -ggdb -o cancel-thread2


/* Questions
1. Is the created thread cancelled ?
2. Why can't we see the created thread's messages (printfs) ?
3. Assuming you hit the "0" key, where is the cancellation point causing the termination ?
4. Please modify the source code so the created thread is terminated by a 
   cancellation point set by you (can you use sleep() ? ).
*/

/* Answers - Barak:
1. The thread is not cnacelled, no cancellation points.
2. why not?
3. in the next printf system call
4. pthread_testchancel(), or sleep()


When cancellation is set to ENABLED, the thread is cancelled on the next printf which is a cancellation point */

/*************  includes     *****************/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>   //sleep()

/*************  Prototypes   *****************/
void* thread1_func(void);

/*************  main() function ****************/ 
// The main program. 
int main ()
{
	pthread_t thread1_id;
	long j;
	int status = 0;

	/* Create a new thread to print 30,000 x's. */
	pthread_create (&thread1_id, NULL, thread1_func, NULL);

	sleep (3);
	printf("main():  Cancel the created thread\n");
	/* Cancel the first thread */
	status = pthread_cancel(thread1_id);
	if (status) printf("main(): cancelation failed\n\r");

	for(;;)
	{
		printf("main():  main has completed and is in an endless loop\n");
		for(j=0;j<0xfffffff;j++);
	}

	return 0;
}

/*************  thread1_func() function ****************/
void* thread1_func(void)
{
	int i,ch;
	pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, NULL);
	printf("thread1_func():  Cancelation is disabled %d\n",i);
	for (i = 0; ; ++i)
		{
			pthread_testcancel();
			printf("thread1_func():  loop number %d\n",i);
			printf("thread1_func():  press only 0 to enable cancelation\n");
			ch=getchar();
			if (ch == '0')
			{
				printf("thread1_func():  Cancelation is enabled %d\n",i);
				pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
				//sleep(1);
			}
		}
	return NULL;
}



