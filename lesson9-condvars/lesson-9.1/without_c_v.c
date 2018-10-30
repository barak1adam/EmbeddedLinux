/* wating for a signal with-out the use of condition variables

Description
-----------
 The exercise illustates waiting for an event to occure without the usage of condition variables
 as you may notice it is very combersome .

the read thread should wait for the write to run first. the write thread will signal the read thread thats its done.



To compile me for Linux, use gcc -ggdb without_c_v.c -lpthread -o without_c_v 
To execute, type:  ./without_c_v 
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
#define NUM_THREADS 2


/*************  Prototypes   *****************/
void* read_function (void* arg);
void* write_function (void* arg);

void do_work();


/*************  Globals   *****************/
int thread_flag = 0;
pthread_mutex_t mutex1;


/*************  main() function ****************/ 
int main() 
{
	//int thread_flag;
	pthread_t th1,th2;
	
	
	//void initialize_flag ()
	pthread_mutex_init (&mutex1, NULL);
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

	while (1)
	 {
		int flag_is_set;
		/* Protect the flag with a mutex lock. */
		if ((rtn = pthread_mutex_lock(&mutex1)) != 0)
		{
   	   		fprintf(stderr,"pthread_mutex_lock: %s",strerror(rtn));
	   		exit(-1);
        	}
		flag_is_set = thread_flag;
		printf ("read_func() flag_is_set= %d\n",flag_is_set);
		
		// unlock the mutex . 
		if ((rtn = pthread_mutex_unlock(&mutex1)) != 0)
		{
   	   		fprintf(stderr,"pthread_mutex_unlock: %s",strerror(rtn));
	   		exit(-1);
        	}
		
		// if the flag is set we can read
		if (flag_is_set)
		{
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
			
			//mark that we have already read
			if ((rtn = pthread_mutex_lock(&mutex1)) != 0)
		 	{
   	   	 		fprintf(stderr,"pthread_mutex_lock: %s",strerror(rtn));
	   			exit(-1);
        		}
			thread_flag = 0;
			
			printf ("read_func() flag_is_set= %d\n",thread_flag);

			if ((rtn = pthread_mutex_unlock(&mutex1)) != 0)
			{
   	   			fprintf(stderr,"pthread_mutex_unlock: %s",strerror(rtn));
	   			exit(-1);
        		}
		}	
		else
		{
		/*else, sleep and try again */
		printf ("read_func() flag_is_set= %d so I will sleep and try again\n",thread_flag);
			sleep(3);
		}
	}
return NULL;
}
/*************************************************************************************/
/* write_function is called once  */
void* write_function (void* thread_arg)
{

	int rtn=-1;
	int local_fd=-1;
	char write_buffer[]="dddddddddddddddddddddddddddddddddd";
	int length=0;
	

		int flag_is_set;
		local_fd = open ("//tmp//a.txt", O_RDWR|O_CREAT,0666); 
		length = write (local_fd, write_buffer, strlen (write_buffer));
		fsync(local_fd);
		printf ("write_func() local_fd=%d length=%d The thread ID is 0x%x the process ID is %d\n",
			local_fd,
			length,
                	(unsigned long) pthread_self (),
                	(int) getpid ());
		close(local_fd);
			
		//set up the global flag to indicate that we are finished writing
		if ((rtn = pthread_mutex_lock(&mutex1)) != 0)
		{
   	   		fprintf(stderr,"pthread_mutex_lock: %s",strerror(rtn));
	   		exit(-1);
        	}
		thread_flag = 1;
			
		printf ("write_func() flag_is_set= %d\n",thread_flag);

		if ((rtn = pthread_mutex_unlock(&mutex1)) != 0)
		{
   			fprintf(stderr,"pthread_mutex_unlock: %s",strerror(rtn));
   			exit(-1);
       		}
	return NULL;
}
/****************************************************************************/


