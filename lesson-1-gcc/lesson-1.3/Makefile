#build=static
#///////////////////////////////////////
ifeq ($(build),static)

libtest.a : test1.o test2.o test3.o
	ar cr -o libtest.a test1.o test2.o test3.o  
test1.o:test1.c 
	gcc -c test1.c
test2.o:test2.c
	gcc -c test2.c
test3.o:test3.c 
	gcc -c test3.c                                     
#///////////////////////////////////////
else

libtest.so : test1.o test2.o test3.o
	gcc -shared -fpic -o libtest.so test1.o test2.o test3.o                                       

test1.o:test1.c 
	gcc -c -fpic test1.c
test2.o:test2.c
	gcc -c -fpic test2.c
test3.o:test3.c 
	gcc -c -fpic test3.c
endif
#////////////////////////////////////////
PHONY : clean

clean :
	rm *.o libtest.* 
