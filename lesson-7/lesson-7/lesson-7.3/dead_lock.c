/* Listing 7.3 ( deadlock.c) this program illustrates causing a deadlock 

Description
-----------
 this is an example of causing a dead lock bu using using pthread_mutex
 

To compile me for Linux, type:  gcc dead_lock.c -ggdb -lpthread -o dead_lock
 To execute, type:  ./dead_lock
 */


/* Questions
1. how can you see that a dead lock has occured?
2. what is the best way to avoide it
3.please fix the code to avoide deadlock 
*/

/* Answers - Barak:
1. 
thread 1 takes mutex m1
thread 2 takes mutex m2
thread 1 is trying to take m2 and is blocking on m2
thread 2 is trying to take m1 and is blocking on m1
thread 1 is waiting for thread 2 which is waiting for thread 1
2. best way to avoid deadlock is to take the mutex in all threads on the same order.
(e.g. m1,m2, m3 ....)
otherwise use pthread_mutex_trylock()



/*************  includes     *****************/

#include <pthread.h>
#include <stdio.h>

/*************  definitions     *****************/
#define NUM_THREADS 2

/*************  Prototypes   *****************/
void * thread_1_func(void *);
void * thread_2_func(void *);


/*************  Globals   *****************/

/* A mutex protecting the data. */
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;



/*************  main() function ****************/ 
int main() 
{
  int i, ret;
  pthread_t tid[NUM_THREADS];      /* array of thread IDs */
	
  pthread_mutex_init(&mutex1, NULL);  //init the mutex 
  pthread_mutex_init(&mutex2, NULL);  //init the mutex 
  
  pthread_create(&tid[0], NULL, thread_1_func, NULL);
  pthread_create(&tid[1], NULL, thread_2_func, NULL);
  
  for ( i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(tid[i], NULL);
  }

  printf("main() reporting that all %d threads have terminated\n", i);
  
  return 0;

}  /* main */

  


/*************  thread_1_func() function ****************/
void * thread_1_func(void *un_used_param)
{
   int i;
   printf("I amthe 1st thread thread_id = 0x%x!\n",pthread_self());
  
   pthread_mutex_lock(&mutex1); 
   printf("thread_1_func() thread_id=%x   mutex1 has been locked \n",pthread_self());

   sleep(10);
   
   pthread_mutex_lock(&mutex2); 
   printf("thread_1_func() thread_id=%x   mutex2 has been locked \n",pthread_self());
   
   

   pthread_mutex_unlock(&mutex2); 
   printf("thread_1_func() thread_id=%x   mutex2 has been unlocked \n",pthread_self());
   
   pthread_mutex_unlock(&mutex1); 
   printf("thread_1_func() thread_id=%x   mutex1 has been unlocked \n",pthread_self());
   
   pthread_exit(0);
}    


/*************  thread_2_func() function ****************/
void * thread_2_func(void *un_used_param)
{
   int i;
   printf("I am the 2nd thread thread_id = 0x%x!\n",pthread_self());
  
   pthread_mutex_lock(&mutex2); 
   printf("thread_2_func() thread_id=%x   mutex2 has been locked \n",pthread_self());

   sleep(10);

   pthread_mutex_lock(&mutex1); 
   printf("thread_2_func() thread_id=%x   mutex1 has been locked \n",pthread_self());
   
  

   pthread_mutex_unlock(&mutex2); 
   printf("thread_2_func() thread_id=%x   mutex2 has been unlocked \n",pthread_self());
   
   pthread_mutex_unlock(&mutex1); 
   printf("thread_2_func() thread_id=%x   mutex1 has been unlocked \n",pthread_self());
   
   pthread_exit(0);
}    
