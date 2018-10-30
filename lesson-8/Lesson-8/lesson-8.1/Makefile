OBJS = semaphore_1.o job_queue.o 
HDRS = job_queue.h 

queue : $(OBJS)
	gcc $(OBJS) -lpthread  -ggdb -o queue 

semaphore_1.o : semaphore_1.c $(HDRS) 
	gcc -c semaphore_1.c -ggdb

job_queue.o:job_queue.c job_queue.h
	gcc -c job_queue.c -ggdb


PHONY : clean

clean :
	rm *.o
