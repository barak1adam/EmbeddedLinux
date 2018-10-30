   // *****************
   // Demonstrates debugging a process
   #include <stdio.h>

   typedef unsigned short int USHORT;       //typedef defined

   int main()
   {
     USHORT  counter = 0;
     while(1)
	 {
		  printf("counter: %d \n",++counter);

	 }
	
     return 0;
 }

