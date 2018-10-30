 /* Listing 6.6-4 ( cancel-thread4.c) 

Description
-----------


Note: when compiling and link this program be sure to add the -lpthread library:
as the following:

% gcc cancel-thread_4.c -lpthread -o a.out

Barak: clean up handler works only upon thread cancellation or also
when a thread is terminated normally? 
Answer: only when the thread is cancelled.



/*************  includes     *****************/
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


/*************  Macros     *****************/
#define HANDLE_ERR(en, msg) \
               do { errno = en; perror(msg); \
			exit(EXIT_FAILURE);  \
		   } 			     \
		while (0)


/*************  Prototypes   *****************/
static void cleanup_handler(void *arg);
static void* thread1_func(void *arg);


/*************  statics   *****************/
static int gCancellation = 0;
static int cnt = 0;
static int gfd = 0;


/*************  main() function ****************/ 
// The main program. 
int main()
{
    pthread_t thr;
    int s;
    void *res;
    char ch;
	
	printf("main: would you like to cancel the thread -  y (yes), n (no)\n");
	ch=getchar();
	printf("main():  ch=%c\n",ch);
	while (!((ch == 'n') || (ch =='y')))
	{
		printf("main():  be serious, n (no) | y (yes) \n");
	}
	
	if (ch == 'y')
	{
			gCancellation=1;
	}
	
    s = pthread_create(&thr, NULL, thread1_func, NULL);
    if (s != 0)
        HANDLE_ERR(s, "main: pthread_create");

    sleep(2);           /* Allow new thread to run a while */
	
	
	if (ch == 'y')
	{
		printf("main: Canceling thread\n");
		s = pthread_cancel(thr);
		if (s != 0)
			HANDLE_ERR(s, "main: pthread_cancel");
    		
	}
	

    s = pthread_join(thr, &res);
    if (s != 0)
        HANDLE_ERR(s, "main: pthread_join");

    if (res == PTHREAD_CANCELED)
        printf("main: Thread was canceled; cnt = %d\n", cnt);
    else{
        printf("main: Thread terminated normally; cnt = %d\n", cnt);
		if (gfd > 0)
			printf("main: clean up handler was not cleaned; gfd = %d\n", gfd);
		}
      
    exit(EXIT_SUCCESS);
}


/*************  cleanup_handler() function ****************/

static void cleanup_handler(void *arg)
{
     int *the_ptr = *(int **)arg;
     printf("cleanup_handler: Called clean-up handler\n");
     free(the_ptr);
	 close(gfd);
     cnt = 0;
}

/*************  thread1_func() function ****************/
static void* thread1_func(void *arg)
{
     time_t  curr;
     int * ptr;

     printf("thread1_func: New thread started\n");

     ptr= (int*) malloc(sizeof(int));
	 if ( (gfd = open("/home/mrv/mrv", O_RDONLY | O_CREAT, 0666)) < 0 )
 	 {
		perror("failed to open /home/mrv/mrv");
		exit(errno);
	 }

     pthread_cleanup_push(cleanup_handler, &ptr);

     curr = time(NULL);

     while (gCancellation)
     {
           pthread_testcancel();           /* A cancellation point */
           if (curr < time(NULL)) 
	       {
                  curr = time(NULL);
                  printf("thread1_func: cnt = %d\n", cnt);  /* A cancellation point */
                  cnt++;
           }
     }
	 sleep(2);
     pthread_cleanup_pop(1);
     return NULL;
}

