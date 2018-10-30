/* Listing 7.1 ( mutex_1.c) this program comes to solve the race condition created by lesson-6.7 (race_condition_1.c)

Description
-----------
 Simple pthread example using pthread_mutex to ensure mutual exclusion 
 This corrects the bug from race_condition_1.c
 

To compile me for Linux, type:  gcc filename.c -lpthread  -o filename 
 To execute, type:  filename
 */


/* Questions
1. how come this solves the bug?
2. 
*/


/*************  includes     *****************/

#include <pthread.h>
#include <stdio.h>

/*************  definitions     *****************/
#define NUM_THREADS 2

/*************  Prototypes   *****************/
void * adder(void *);


/*************  Globals   *****************/

/* A mutex protecting the data. */
pthread_mutex_t mutex;

int bignum = 0;


/*************  main() function ****************/ 
int main() 
{
  int i, ret;
  pthread_t tid[NUM_THREADS];      /* array of thread IDs */
	
  pthread_mutex_init(&mutex, NULL);  //init the mutex 
  
  for (i=0; i<NUM_THREADS; i++) 
  {
    pthread_create(&tid[i], NULL, adder, NULL);
  }
  
  for ( i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(tid[i], NULL);
  }

  printf("main() reporting that all %d threads have terminated\n", i);
  printf("I am main! bignum=%d\n", bignum);
  
  return 0;

}  /* main */

  


/*************  adder() function ****************/
void * adder(void * parm)
{
   int i;
   printf("I am a new thread!\n");
   pthread_mutex_lock(&mutex); 
   for(i=0;i<100000;i++) 
   {
       bignum++;   
       printf("adder() thread_id=%x   bignum = %d\n",pthread_self(), bignum);
   }
   pthread_mutex_unlock(&mutex); 
   pthread_exit(0);
}    


