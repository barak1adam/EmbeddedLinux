/*
 * shm-client - client program to demonstrate shared memory.
 *


Description
-----------
 This processes aims to read the written text by the the server process
 first it finds the identifier used of the server program.
 Then it attaches to the segment and reads from it.
 Finally it changes the first character of the segment to '*', indicating that the segmenthas been read.


To compile me for Linux, use: gcc shared_mem_client.c -ggdb -o shared_client 


To execute, type:  ./shared_client
 */


/* Barak - integrate system V semaphores */
#include "./Sys_V_Sem.h"

/*************  includes     *****************/
#include <sys/shm.h>

/*************  definitions     *****************/
#define SHMSZ     27


/*************  Prototypes   *****************/


/*************  Globals   *****************/



/*************  main() function ****************/
main()
{
    int shmid;
    key_t key;
    char *shm, *s;
	
    /*
	* We need to get the segment named
	* "5678", created by the server.
	*/
    key = 5678;
	
    /*
	* Locate the segment.
	*/
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
	
    /*
	* Now we attach the segment to our data space.
	*/
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
	
    /*
	* Now read what the server put in the memory.
	*/
    if (lock_sys_v_sem() != 0) 
    { 
        perror("lock_sys_v_sem"); 
        exit(1); 
    }
    for (s = shm; *s != (char)0/*NULL*/; s++)
        putchar(*s);
    putchar('\n');
	
    if (unlock_sys_v_sem() != 0) 
    { 
        perror("unlock_sys_v_sem"); 
        exit(1); 
    }
    /*
	* Finally, change the first character of the 
	* segment to '*', indicating we have read 
	* the segment.
	*/
    *shm = '*';
	
    exit(0);
}

