/* Listing 7.2 ( mutex_2.c) this program creates the race condition created in lesson 6.8 (race_condition_2.c)

Description
-----------
 The solution to the job queue race condition problem is to let only one thread access
the queue of jobs at a time. Once a thread starts looking at the queue, no other thread
should be able to access it until the first thread has decided whether to process a job
and, if so, has removed the job from the list.
   
Implementing this requires support from the operating system. GNU/Linux provides mutexes, 
short for MUTual EXclusion locks. 




To compile me for Linux, use the makefile attached 
 To execute, type:  ./mutex_2
 */


/* Questions
1. How is the bug solved?
2. Can u see any other potential bugs which might occure ?
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
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;               // A mutex protecting job_queue. 

job_t *job_queue=NULL;


/*************  main() function ****************/ 
int main() 
{
  pthread_t tid[NUM_THREADS];      /* array of thread IDs */
  int i;
  int stat = -1;
  job_t *head=NULL;
  job_t *tail= NULL;

  stat = init_job_queue(&head,&tail);
  
  job_queue = head;      //update global ptr

  for (i=0; i<NUM_THREADS; i++) 
  {
    pthread_create(&tid[i], NULL, thread_function,NULL);
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
  
   job_t* current_job = NULL;
   printf("thread_function() thread_id = 0x%lx  job_queue=0x%p \n", 
	  pthread_self(),
	  (int*)job_queue);	
   
   while (1) 
   {
     
     /* Lock the mutex on the job queue. */
    pthread_mutex_lock (&job_queue_mutex);
    
    /* Now it’s safe to check if the queue is empty. */
    if (job_queue == NULL)
      current_job = NULL;
    else 
    {
      /* Get the next available job. */
      current_job = job_queue;
      /* Remove this job from the list. */
      job_queue = job_queue->next;
    }
    /* Unlock the mutex on the job queue because we’re done with the
       queue for now. */
    pthread_mutex_unlock (&job_queue_mutex);
 
   /* Was the queue empty?  If so, end the thread.  */
    if (current_job == NULL)
      break;
  
   /* Carry out the work. */
    process_job (current_job);
    /* Clean up. */
    free (current_job);
  }
    
  return NULL;
}


/*************  process_job() function ****************/
int process_job(job_t* the_job)
{
   int i;
   printf("process_job() thread_id=0x%lx the_job=0x%p data = %d\n",
	  pthread_self(),
	  (int*)the_job,
	  the_job->data);
   
   return (0);
}    
