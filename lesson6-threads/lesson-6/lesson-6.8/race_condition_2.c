/* Listing 6.8 ( race_condition_2.c) this program creates a race condition

Description
-----------
This program creates threads which handle jobs from the job queue.
The queue of jobs is represented by a linked list of struct job objects on the heap, 
with series of queued jobs as members.

The jobs are processed by several concurrent threads.
The main function defines a local pointer - head, to the begining of the Linked List
the local pointer head is duplicated every time a thread is created, so basicly each one of the threads 
has a pointer pointing to the allocated job-queue element.


After each thread finishes an operation, it checks the queue to see if an additional
job is available. If job_queue is non-null, the thread removes the head of the linked list
and sets job_queue to the next job on the list.
 


To compile me for Linux, type:  gcc filename.c -lpthread  -o filename 
 To execute, type:  filename
 */


/* Questions
1. How many times does the 2nd thread run?   
2. how many bugs are there in this program?
3. will the bug be caused every time u run the program ?
4. change the number of elements to 100000
5. how can you avoid the bug
*/


/*************  includes     *****************/

#include <pthread.h>
#include <stdio.h>
#include "job_queue.h"

/*************  definitions     *****************/
#define NUM_THREADS 2


/*************  Prototypes   *****************/
void* thread_function (void* arg);
int process_job(job_t* the_job);


/*************  Globals   *****************/


/*************  main() function ****************/ 
int main() 
{
  pthread_t tid[NUM_THREADS];      /* array of thread IDs */
  int i;
  int stat = -1;
  job_t *head=NULL;
  job_t *tail= NULL;

  stat = init_job_queue(&head,&tail);

  for (i=0; i<NUM_THREADS; i++) 
  {
    pthread_create(&tid[i], NULL, thread_function, (void *) &head);
  }
  
  for ( i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(tid[i], NULL);
  }

  printf("main() reporting that all %d threads have terminated\n", i);
  
  return 0;

}

/*************  thread_function() function ****************/
/* Process queued jobs until the queue is empty.   */
void* thread_function (void* arg)
{
   job_t* job_queue;
   job_queue = *((job_t **) arg);

   printf("thread_function() thread_id = 0x%lx \n", pthread_self());	
   while (job_queue != NULL) 
   {
     
     /* Get the next available job. */
     job_t* current_job = job_queue;
     /* Remove this job from the list. */
     job_queue = job_queue->next;
     /* Carry out the work. */
     process_job (current_job);
     /* Clean up. */
     free (current_job);
   }
   return ( NULL);
}


/*************  process_job() function ****************/
int process_job(job_t* the_job)
{
   int i;
   printf("process_job() thread_id=0x%lx the_job=0x%p data = %d\n",
      pthread_self(),
      (int*)the_job,the_job->data);
   
   return (0);
}    
