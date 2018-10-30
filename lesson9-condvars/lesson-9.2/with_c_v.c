/* wating for a signal with the use of condition variables

Description
-----------
 The exercise illustates waiting for an event to occure with the usage of condition variables
 as you may notice it is much easier than the previous one. .

the read thread should waits on the condition variable.



To compile me for Linux, use gcc -ggdb with_c_v.c -lpthread -o with_c_v 
To execute, type:  ./with_c_v 
 */



/*************  includes     *****************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>             //used for exit
#include <string.h> 


#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <error.h>


/*************  definitions     *****************/


/*************  Prototypes   *****************/
void* read_function (void* arg);
void* write_function (void* arg);



/*************  Globals   *****************/
int thread_flag = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var;


/*************  main() function ****************/ 
int main() 
{
	//int thread_flag;
	pthread_t th1,th2;
	/*pthread_mutexattr_t Attr;

	pthread_mutexattr_init(&Attr);
	pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);*/	
	
	/* Initialize the mutex1. */
	//pthread_mutex_init (&mutex1, /*&Att*/NULL);
	/* Initialize the condition variable. */
	pthread_cond_init (&cond_var, NULL);
	/* Initialize the flag value. */
	thread_flag = 0;

	
	pthread_create(&th1, NULL, read_function,NULL);
	pthread_create(&th2, NULL, write_function,NULL);
	

	sleep(15);

 	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	
	return 0;

}


/*************************************************************************************/
/* Calls do_work repeatedly while the thread flag is set; otherwise
spins. */
void* read_function (void* thread_arg)
{
	
	int rtn=-1;
	int local_fd=-1;
        int length=0;
	char read_buffer[80];
	int id;
	
	/* Lock the mutex before accessing the flag value. */
	if ((rtn = pthread_mutex_lock(&mutex1)) != 0)
	{
   		fprintf(stderr,"pthread_mutex_lock first: %s",strerror(rtn));
		exit(-1);
        }
	if ((rtn = pthread_mutex_lock(&mutex1)) != 0)
	{
   		fprintf(stderr,"pthread_mutex_lock second: %s",strerror(rtn));
		printf("errrrrrrrror recursive lock \n");
		exit(-1);
    }
#if 1	
	 /* Unlock the mutex. */
	if ((rtn = pthread_mutex_unlock(&mutex1)) != 0)
	{
   		fprintf(stderr,"pthread_mutex_unlock: %s",strerror(rtn));
		exit(-1);
    }
#endif
	printf("got here after double lock \n");

	while (!thread_flag)
	{
    		/* The flag is clear. Wait for a signal on the condition
       	   	variable, indicating that the flag value has changed. When the
       	   	signal arrives and this thread unblocks, loop and check the
       		flag again.
       		the call to pthread_cond_wait()  unlocks the mutex so the the other thread (write_function)
       		can use it */
		    printf ("read_func() thread_flag= %d got into wait state\n",thread_flag);
    		pthread_cond_wait (&cond_var, &mutex1);
  		/* When we"ve gotten here, we know the flag must be set, the call to pthread_cond_signal() waked up the thread 
  		   and locked the mutex don"t forget, mutex can be locked recursevly */
		  /* Barak - Nothing related to recursively locking the mutex:
		  	1. recursive lock on mutex is done only by the calling (owning) thread
			2. recursive lock should be enabled on mutex init.
			The order of actions is the following:
			read thread lock the mutex //th1 lock
			read thread is calling pthread_cond_wait (&cond_var, &mutex1): 
				pthread_cond_wait unlock the mutex and block ! //th1 unlock
			write thread is writing to file
			write thread lock the mutex //th2 lock
			write thread setting the flag and then pthread_cond_signal(): 
				when signaling, read thread pthread_cond_wait is unblocked and relock the mutex again automatically
			write thread is unlocking the mutex
			read thread is unlocking the mutex and go for blocking on the file for reading.
		   */
	}
	printf ("read_func() thread_flag= %d got out of wait state\n",thread_flag);

	 /* Unlock the mutex. */
	if ((rtn = pthread_mutex_unlock(&mutex1)) != 0)
	{
   		fprintf(stderr,"pthread_mutex_unlock: %s",strerror(rtn));
		exit(-1);
    }

		
	local_fd = open ("//tmp//a.txt", O_RDWR|O_CREAT,0666); 
	printf ("read_func() local_fd =%d The thread ID is 0x%x the process ID is %d\n",
		local_fd,
        	(unsigned long) pthread_self (),
        	(int) getpid ());
	
	/* Read the size of the data in the  file. */
	length = read (local_fd, read_buffer, sizeof (read_buffer));
	printf ("read_func() local_fd=%d length=%d read_buffer=%s\n",
		local_fd,
		length,
		read_buffer);
	
	close(local_fd);
		
	return NULL;
}
/*************************************************************************************/
/* Calls do_work repeatedly while the thread flag is set; otherwise
spins. */
void* write_function (void* thread_arg)
{

	int rtn=-1;
	int local_fd=-1;
	char write_buffer[]="dddddddddddddddddddddddddddddddddd";
	int length=0;
	
	local_fd = open ("//tmp//a.txt", O_RDWR|O_CREAT,0666); 
	length = write (local_fd, write_buffer, strlen (write_buffer));
	fsync(local_fd);
	printf ("write_func() local_fd=%d length=%d The thread ID is 0x%x the process ID is %d\n",
	        local_fd,
		length,
                (unsigned long) pthread_self (),
                (int) getpid ());
	close(local_fd);
	
	/* Lock the mutex before accessing the flag value. */
	if ((rtn = pthread_mutex_lock(&mutex1)) != 0)
	{
   		fprintf(stderr,"pthread_mutex_lock: %s",strerror(rtn));
		exit(-1);
        }
	/* Set the flag value, and then signal read_function in case it is
           blocked, waiting for the flag to become set. 
           the pthread_cond_signal() lockes the mutex again on thread's A behalf

           However, read_function can"t actually check the flag until the mutex is
           unlocked. */

	thread_flag = 1;
	pthread_cond_signal (&cond_var);
	printf ("write_func() thread_flag= %d signal to call read_func\n",thread_flag);
	/* Unlock the mutex. */
	if ((rtn = pthread_mutex_unlock(&mutex1)) != 0)
	{
   	 	fprintf(stderr,"pthread_mutex_unlock: %s",strerror(rtn));
	 	exit(-1);
        }
		
			
		
	return NULL;
}
/****************************************************************************/

