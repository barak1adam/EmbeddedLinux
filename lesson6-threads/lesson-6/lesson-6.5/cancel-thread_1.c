/* Listing 6.5 ( cancel-thread1.c) trying to kill a newly created thread.

Description
-----------
trying to kill a newly created thread.

Note: when compiling and link this program be sure to add the -lpthread library:
as the following:

% gcc cancel-thread_1.c -lpthread -ggdb -o cancel-thread_1



/* Questions
1. What is the stat variable used for? 
   does it indicate that the target thread is terminated ?
2. Why is there a need for the 3 seconds sleep ? (line 43)
3. Is the created thread terminated ? WHY is that ? 
4. Please modify the source code so the created thread is terminated at the 9th itteration
*/

/* Answers - Barak:
1. The return status of pthread_cancel() merely informs the caller whether the cancellation request was successfully
       queued. It doesn't indicate that the thread is terminated. To get terminated the thread has to:
	   --get CPU time to handle the cancellation request.
	   --be in cancelbale. (enabled + async or enabled+asynced+cancellation points)
2. A sleep is needed to give the thread a chance to get CPU time and run
3 .It is not terminate because it's cancelation state and type is enabled + deffered by default. so it has to 
have cancellation points.
4. Need to add a cancellation point explicitly or a system call which is already cancelable.

/*************  includes     *****************/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>   //sleep()

/*************  Prototypes   *****************/
void* thread1_func();
int gCounter=0;
int changed = 0;



/*************  main() function ****************/ 
// The main program. 
int main ()
{
	pthread_t thread1_id;
	int stat =-1;

	/* Create a new thread to print 30,000 x's. */
	pthread_create (&thread1_id, NULL, thread1_func, NULL);

	sleep (3);

	printf("main():  Cancel the created thread\n");
	/* Cancel the thread */
	stat = pthread_cancel(thread1_id);
	
	while(1)
	{
		if (changed){
			printf("main():  gCounter=%d \n",gCounter);
			changed = 0;
		}
		
	}
	

	/* Now we can safely return. */
	return 0;
}

/*************  thread1_func() function ****************/
/* Prints a number of characters to stderr, as given by PARAMETERS,
which is a pointer to a struct char_print_parms. */
void* thread1_func(void)
{
	int i,j;
	for (i = 0; ; ++i)
	{
		if (i == 9) pthread_testcancel();
		for(j=0;j<0xfffffff;j++);
		gCounter++;
		changed = 1;
		
	}
	return NULL;
}



