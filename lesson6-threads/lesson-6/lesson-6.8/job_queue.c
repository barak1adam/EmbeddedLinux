#include "job_queue.h"

/******************************************************************************************/
//Globals
/******************************************************************************************/
int k=0;   //index for data
int const num_of_elements = 10;


/******************************************************************************************/
//init_job_queue()
/******************************************************************************************/
int init_job_queue(job_t **head,job_t **tail)
{
	int status =-1;
	int i=0;
	
	*head= (job_t*) malloc(sizeof(job_t));
	*tail= *head;
	(*head)->next =NULL;
	(*head)->data = 0;
	
	for(i=0;i<num_of_elements;i++)
	{	
		status = add_node_to_head(head);
		if(status==-1)
		{
			return -1;
		}
	}
	
	return 0;
}

/******************************************************************************************/
//add_node_to_head
/******************************************************************************************/
int add_node_to_head(job_t** head)
{
	
	job_t *tmp=NULL;
	

	//allocate new Node
	tmp = (job_t*)malloc(sizeof(job_t));
	if(tmp==NULL)
	{
		return -1;
	}
	
	
	//concatinate to list
	tmp->next=*head;
		
	//give values to Node
	tmp->data=++k;
	
		
	//head should always point tofuest item
	*head=tmp;
	

	return 0;
}
/******************************************************************************************/
//remove_node_from_head
/******************************************************************************************/
void remove_node_from_head(job_t** head)
{
	job_t *tmp=*head;
	
	*head = tmp->next;

	free (tmp);

	return ;		
}
/******************************************************************************************/


