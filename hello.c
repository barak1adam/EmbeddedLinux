/*
* Hello World program
*/

#include <stdio.h>
#include <pthread.h>

extern void func1(void);

int main(void)
{
	int i;
	pthread_t thr;

	printf("Hello Linux Programming World\n");
	pthread_create(&thr, NULL, (void *)&func1, NULL);
	return 0;
}
