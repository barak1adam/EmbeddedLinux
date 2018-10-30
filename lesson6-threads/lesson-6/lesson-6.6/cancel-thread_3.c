/* Listing 6.6 ( cancel-thread3.c) 

Description
-----------
Trying to terminate a newly created thread which is configured as:
	PTHREAD_CANCEL_DISABLE and
	PTHREAD_CANCEL_DEFERRED

Note: when compiling and link this program be sure to add the -lpthread library:
as the following:

% gcc cancel-thread3.c -lpthread -ggdb -o cancel-thread3



/*************  includes     *****************/
#include <pthread.h>
#include <stdio.h>


/*************  Prototypes   *****************/
void* thread1_func();




/*************  main() function ****************/ 
// The main program. 
int main ()
{
	pthread_t thread1_id;
	long j;

	/* Create a new thread to print 30,000 x's. */
	pthread_create (&thread1_id, NULL, thread1_func, NULL);

	sleep (1);
	printf("main():  Cancel the created thread\n");
	/* Cancel the first thread */
	pthread_cancel(thread1_id);

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
	pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED, NULL);
	printf("thread1_func():  Cancelation is DISABLED at this point\n");
	for (i = 0;i<10; ++i)
	{
        sleep(1);
		printf("thread1_func():  loop number %d\n",i);
	}
    printf("thread1_func():  setting a Cancelation point\n");
	pthread_testcancel();

 	printf("thread1_func():  Cancelation is ENABLED Synchronously %d\n");
	pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
	return NULL;
}



