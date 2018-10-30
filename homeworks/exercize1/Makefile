#Make file with variables for Exc.1, Question1

OBJS = main.o question1.o serial.o
HDRS = q1.h serial.h
GCC_OPTS = -ggdb
	
main : $(OBJS)
	gcc -o ex1q1 $(OBJS)

question1.o :  question1.c $(HDRS)
	gcc $(GCC_OPTS) -c question1.c

main.o :  main.c $(HDRS)
	gcc $(GCC_OPTS) -c main.c

serial.o :  serial.c serial.h
	gcc $(GCC_OPTS) -c serial.c



PHONY : clean
clean :
	rm $(OBJS) ex1q1
