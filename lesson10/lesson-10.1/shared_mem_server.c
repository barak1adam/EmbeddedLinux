/*
 * shared_mem_server.c -  creates a shared memory portion and writes to it.
 *

  Description
  -----------
  This processes allocates the shared Memory area, then it attaches to it.
  It writes into the memory segment for the other process to read.
  Finally we wait until the other process changes the first character of the memory
  to '*', indicating that it has read the string.
  
	
	  
  To compile me for Linux, use: gcc shared_mem_client.c -ggdb -o shared_server 
 
  To execute, type:  ./shared_server
*/

/*************  includes     *****************/
#include <sys/shm.h>

/* Barak - integrate system V semaphores */
#include "./Sys_V_Sem.h"

/*************  definitions     *****************/
#define SHMSZ     27

/*************  Prototypes   *****************/


/*************  Globals   *****************/


/*************  main() function ****************/
main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
	
    if (init_sys_v_sem() != 0) 
    { 
        perror("init_sys_v_sem"); 
        exit(1); 
    } 
    
	/*
	* We'll name our shared memory segment
	* "5678".
	*/
    key = 5678;
	
    /*
	* Create the segment.
	*/
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
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
	* Now put some things into the memory for the
	* other process to read.
	*/
    s = shm;
	
    if (lock_sys_v_sem() != 0) 
    { 
        perror("lock_sys_v_sem"); 
        exit(1); 
    }

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = 0/*NULL*/;
	
    if (unlock_sys_v_sem() != 0) 
    { 
        perror("unlock_sys_v_sem"); 
        exit(1); 
    }

    /*
	* Finally, we wait until the other process 
	* changes the first character of our memory
	* to '*', indicating that it has read what 
	* we put there.
	*/
    while (*shm != '*')
        sleep(1);

    exit(0);
}
