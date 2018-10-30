/*************  includes     *****************/
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 

/*************  definitions     *****************/
union semun 
{
	int val;
    struct semid_ds *buf;
    ushort *array;
};

/*************  Prototypes   *****************/
int init_sys_v_sem();
int lock_sys_v_sem();
int unlock_sys_v_sem();

