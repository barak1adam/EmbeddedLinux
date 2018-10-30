   // *****************
   // Demonstrates debugging a program
   #include <stdio.h>

   typedef unsigned short int USHORT;       //typedef defined

   int main()
   {
     USHORT  Width = 5;
     USHORT Length;
     Length = 10;
     USHORT Area  = Width * Length;
     
	 printf("Width: %d \n",Width);
	 printf("Length: %d \n",Length);
	 printf("Area: %d \n",Area);
     
     return 0;
 }

