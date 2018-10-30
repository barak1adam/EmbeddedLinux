/* Listing 6.2 ( create_thread2.c) creating new threads and passing arguments.

Description
-----------

This program is similar to the previous example.
This one creates two new threads:
  - one to print x’s 
  - and the other to print o’s. 

Instead of printing infinitely, each thread prints a fixed number of
characters and then exits 

Note: when compiling and link this program be sure to add the -lpthread library:
as the following:

% gcc create-thread2.c -lpthread -o create-thread2


/* Questions
1. Do you see any output ? why not
2. Enable the sleep system call on line 68, what happened , can u explain that 
3. What is a better method to use instead of sleep?
*/


/*************  Includes     *****************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
* */
#include <unistd.h>
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

	// Create a new thread to print 30,000 'x's.
	thread1_args.character = 'x';
	thread1_args.count = 20;
	pthread_create (&thread1_id, NULL, &char_print, &thread1_args);
	printf("thred id 1 = 0x%x \n", thread1_id);


	// Create a new thread to print 20,000 o's. 
	thread2_args.character = 'o';
	thread2_args.count = 20;
	pthread_create (&thread2_id, NULL, &char_print, &thread2_args);
	printf("thred id 2 = 0x%x \n", thread2_id);

	sleep(10);
	
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
	{
		fputc (p->character, stderr);
		printf ("I'm a thread: threadid=0x%x pid=%d, ppid=%d\n", pthread_self(), getpid(), getppid());
		sleep(1);
	}
	return NULL;
}



/*
Answer
-------
This program has a serious bug in it. 
The main thread (which runs the main function) creates the thread parameter structures 
(thread1_args and thread2_args) as local variables, and then passes pointers 
to these structures to the threads it creates.

What’s to prevent Linux from scheduling the three threads in such a
way that main finishes executing before either of the other two threads are done?

The memory containing the thread parameter structures will be deallocated |
while the other two threads are still accessing it.

*/
