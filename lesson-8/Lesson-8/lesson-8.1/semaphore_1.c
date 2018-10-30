/* Listing 8.1 ( mutex_2.c) this program keeps the threads blocked wating for new jobs 

Description
-----------
 Regarding the job queue exercise,
 When the queue runs out of jobs the threads are blocked wating for jobs,
 this is done through the counter semaphores   


 To compile me for Linux, use the makefile attached 
 To execute, type:  ./queue
 */


/* Questions
1. how were we able to put the threads to sleep when there are No additional jobs?
2. can u see any other bugs which may occure ?
*/


/*************  includes     *****************/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <semaphore.h>
#include "job_queue.h"

/*************  definitions     *****************/
#define NUM_THREADS 2


/*************  Prototypes   *****************/
void* thread_function (void* arg);
int process_job(job_t* the_job);
void* add_job (void* arg);


/*************  Globals   *****************/
 // A mutex protecting the job_queue.
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;               

// A linked list of pending jobs.
job_t *job_queue=NULL;        

// A semaphore counting the number of jobs in the queue.
sem_t job_queue_count;    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




/*************  main() function ****************/ 
int main() 
{
  pthread_t th,tid[NUM_THREADS];      /* array of thread IDs */
  int i;
  int stat = -1;
  job_t *head=NULL;
  job_t *tail= NULL;

  
/* Initialize the semaphore which counts jobs in the queue.
   initial value should be zero. */
   sem_init (&job_queue_count, 0, 0); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  stat = init_job_queue(&head,&tail);


  job_queue = head;      //update global ptr

  //this thread inserts jobs into job-queue
  pthread_create(&th, NULL, add_job,NULL);
	 
  for (i=0; i<NUM_THREADS; i++) 
  {
    pthread_create(&tid[i], NULL, thread_function,NULL);
  }

  
  for ( i = 0; i < NUM_THREADS; i++)
  {
	pthread_join(tid[i], NULL);
  }
	
  pthread_join(th, NULL);

  printf("main() reaching here is a proof of a BUG!! reporting that all %d threads have terminated\n", i);
  
  return 0;

}

/*************  thread_function() function ****************/
/* Process queued jobs until the queue is empty.   */
void* thread_function (void* arg)
{
  
   job_t* current_job = NULL;
   printf("thread_function() thread_id = 0x%lx  job_queue=0x%p \n", 
       pthread_self(),
       (int*)job_queue );	
   
   while (1) 
   {
     /* Wait on the job queue semaphore. If its value is positive,
   indicating that the queue is not empty, decrement the count by 1.
   If the queue is empty, block until a new job is enqueued. */
    sem_wait (&job_queue_count);    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

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
/*************  add_job() function ****************/
/* Process queued jobs if the queue is empty.   */
void* add_job (void* arg)
{
	job_t* current_job = NULL;
	
	while(1)
	{
		sleep(3);
		/* Lock the mutex on the job queue. */
		pthread_mutex_lock (&job_queue_mutex);
		printf("add_job() thread_id = 0x%lx  job added job_queue=0x%p \n", pthread_self(),(int*)job_queue);

		/* Now it’s safe to check if the queue is empty. */
		if (job_queue == NULL)
		{
			current_job = (job_t*) malloc(sizeof(job_t));
			(current_job)->next =NULL;
			(current_job)->data = 0;
			sem_post (&job_queue_count);    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			
			add_node_to_head(&current_job);
			job_queue = current_job;                  //update global ptr
			printf("add_job() thread_id = 0x%lx  job added job_queue=0x%p \n", pthread_self(),(int*)job_queue);
		}
			/* unlock the mutex on the job queue. */
		pthread_mutex_unlock (&job_queue_mutex);
	}
 
  return NULL;
}

