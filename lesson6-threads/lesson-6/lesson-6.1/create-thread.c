/* Listing 6.1 ( create thread.c) creating new threads
 * 
 * Description
 * -----------
 * The program in Listing 6.1 creates a thread that prints x’s continuously to standard error. 
 * After calling pthread_create, the main thread prints o’s continuously to standard error.
 * 
 * Note: when compiling and link this program be sure to add the -lpthread library:
 * as the following:
 * 
 * % gcc create-thread.c -lpthread -o create-thread
 * 
 * when running the program, Notice the unpredictable pattern of x’s and o’s as
 * Linux alternately schedules the two threads.
 * 
 *
 * 
 * Questions
 * -----------
 * 1. is the amount of x's and o's equal? remove remarks on lines 59 and 72, build and run again
 * 2. when is the new thread being contex switched
 * 3. why do we need a global variable?
 * 
 */


/*************  Includes     *****************/
#include <pthread.h>
#include <stdio.h>

/*************  Prototypes   *****************/
void* print_xs (void* unused);

/*************  Globals   ********************/
int num_of_x = 0;

/*************  main() function ****************/ 
/* The main program. */
int main ()
{
	pthread_t thread_id;
	
	int num_of_o = 0;
	
	// Create a new thread. The new thread will run the print_xs function.
	pthread_create (&thread_id, NULL, &print_xs, NULL);

	// Print o"s continuously to stderr. 
	while (1)
		{
		  	fputc ('o', stderr);
		  	printf("   num-of-o = %d\n",++num_of_o);
		}
		
	return 0;
}

/*************  print_xs() function ****************/
/* Prints x"s to stderr. The parameter is unused. Does not return. */
void* print_xs (void* unused)
{
	while (1)
		{
			fputc ('x', stderr);
			printf("    num-of-x = %d\n",++num_of_x);
		}
		
	return NULL;
}


