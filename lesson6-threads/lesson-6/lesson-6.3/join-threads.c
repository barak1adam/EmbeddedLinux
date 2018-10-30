/* Listing 6.3 ( join_threads.c) creating new threads and passing arguments.

Description
-----------
in order to fix the bug in the previous program we have to force main to wait until the other two threads are done.
What we need is a function similar to wait that waits for a thread to finish instead of a process.
That function is pthread_join(), 


Note: when compiling and link this program be sure to add the -lpthread library:
as the following:

% gcc join-threads.c -lpthread -ggdb -o join-threads



/* Questions
1. what have we achived by using pthread_join()?
2  are we able to do it otherwise ?
*/


/*************  includes     *****************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
*/
#include <pthread.h>
#include <stdio.h>

/*************  Prototypes   *****************/
void* char_print (void* parameters);


/*************  Structures   *****************/
// Parameters to print_function. 
struct char_print_parms
{
	char character;    // The character to print
	int count;         // The number of times to print it.
};


/*************  main() function ****************/ 
// The main program. 
int main ()
{
pthread_t thread1_id;
pthread_t thread2_id;
struct char_print_parms thread1_args;
struct char_print_parms thread2_args;

/* Create a new thread to print 30,000 x's. */
thread1_args.character = 'x';
thread1_args.count = 30000;
pthread_create (&thread1_id, NULL, &char_print, &thread1_args);


/* Create a new thread to print 20,000 o's. */
thread2_args.character = 'o';
thread2_args.count = 30000;
pthread_create (&thread2_id, NULL, &char_print, &thread2_args);


/* Make sure the first thread has finished. */
pthread_join (thread1_id, NULL);
/* Make sure the second thread has finished. */
pthread_join (thread2_id, NULL);


/* Now we can safely return. */
return 0;
}

/*************  char_print() function ****************/
/* Prints a number of characters to stderr, as given by PARAMETERS,
which is a pointer to a struct char_print_parms. */
void* char_print (void* parameters)
{
	// Cast the cookie pointer to the right type. 
	struct char_print_parms* p = (struct char_print_parms*) parameters;
	int i;
	for (i = 0; i < p->count; ++i)
		fputc (p->character, stderr);
	return NULL;
}



