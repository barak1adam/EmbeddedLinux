SERV_OBJS = shared_mem_server.o sys_v_sem.o
HDRS = Sys_V_Sem.h 

shared_server: $(SERV_OBJS)
	gcc $(SERV_OBJS) -ggdb -o shared_server 

shared_mem_server.o: shared_mem_server.c $(HDRS)
	gcc -c shared_mem_server.c -ggdb

sys_v_sem.o: Sys_V_Sem.c $(HDRS)
	gcc -c Sys_V_Sem.c -ggdb -o sys_v_sem.o

PHONY : clean

clean :
	rm *.o
