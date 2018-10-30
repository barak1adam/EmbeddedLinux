OBJS = mutex_2.o job_queue.o 
HDRS = job_queue.h 

queue : $(OBJS)
	gcc $(OBJS) -lpthread  -ggdb -o queue 

mutex_2.o : mutex_2.c $(HDRS) 
	gcc -c mutex_2.c -ggdb

job_queue.o:job_queue.c job_queue.h
	gcc -c job_queue.c -ggdb


PHONY : clean

clean :
	rm *.o
