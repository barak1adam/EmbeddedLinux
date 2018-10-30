/* Listing 6.7 ( race_condition_1.c) this program creates a race condition

Description
-----------
 Simple pthread race example 
 THIS CODE HAS A BUG IN IT!  
 


To compile me for Linux, type:  gcc filename.c -lpthread  -o filename 
 To execute, type:  ./filename
 */


/* Questions
1. Where is the bug in this program?
2. will it be caused every time u run the program ?
3. how can you avoid the bug
*/

/* Barak - Answers:
1. threads writing to a shared variable "bignum" without sync: bignum++
one thread might increment it to 99999, then the other one might increment it to 1...
2. depends on how the threads are scheduled
3. mutex
*/


/*************  includes     *****************/
#include <pthread.h>
#include <stdio.h>

/*************  definitions     *****************/
#define NUM_THREADS 5

/*************  Prototypes   *****************/
void * adder(void *);


/*************  Globals   *****************/
pthread_t tid[NUM_THREADS];      /* array of thread IDs */

int bignum = 0;


/*************  main() function ****************/ 
int main() 
{
  int i, ret;

  
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
   for(i=0;i<100000;i++) 
   {
       bignum++;   
       printf("adder() thread_id=%x   bignum = %d\n",pthread_self(), bignum);
   }
   pthread_exit(0);
}    


