#ifndef __JOB_QUEUE_H_
#define __JOB_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

/*************  structures     *****************/
struct job  
{
   int data;
   /*  fields describing work to be done... */

   struct job* next;  // Link field for linked list.  
};
typedef struct job job_t;


/******************************************************************************************/
//Prototypes
/******************************************************************************************/
int init_job_queue(job_t **head,job_t **tail);
int add_node_to_head(job_t** head);
void remove_node_from_head(job_t** head);


/******************************************************************************************/
//Externs
/******************************************************************************************/
extern sem_t job_queue_count;

#endif //__JOB_QUEUE_H_


