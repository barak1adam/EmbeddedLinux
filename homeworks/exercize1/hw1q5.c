#include <stdio.h>

/* Bishki -  I put many comments for you...
   --you can remove part of the comments and calls to printf().
   --Some comments are always nice to have for the reader
   --anyway, there are more options to make this question, but here just a simple example 
   to make it clear for you.
   --don't worry, you will understand everything !
   --use as many printf() as you can, it is very helpful. */

int main()
{
   /* an input example: 30 10 10 10 20 20 40 0 */

   /* n will store each integer value entered by the user */
   int n = 0;
   /* first will store the first value, e.g. 30 */
   int first = 0;
   /* last will store the last value, e.g. 40 */
   int last = 0;
   /* sum will store the sum of all value between first and last, e.g.: 10, 10, 10, 20, 20 */
   int sum = 0; 

   printf("Enter at least 3 INT values:\n");
   printf("============================\n");
   
   /* get the first value and save it into 'first' variable */
   scanf("%d", &first);
   printf("First value is: %d\n\r", first);

	/* in the following loop: 
		1. save last value scanned 
		2. add it to sum
		3. get a new value from the user with scanf
		4. if we get '0' from the user, break out of the loop */

	do {
		/* 1. save last value scanned before getting a new one */
		last = n;
		/* print last value. Not must, just to make it clear... */
		printf("Last value is: %d\n\r", last);
		/* 2. add last input value into 'sum' variable */
		sum += last; /* it is the same like sum = sum + last; */
		/* print sum value. Not must, just to make it clear... */
		printf("Sum value is: %d\n\r", sum);

		/* 3. get a new value from the user with scanf */
		printf("\nEnter next INT value:");
		scanf("%d", &n);
	} while (n != 0);
	
	/* if we out of the loop, this is because we've got '0' into 'n'
	   so substract last from sum, sum should have only values between first and last ... */
	sum -= last;
	
	/* print sum, first and last, Not must, just to make it clear... */
	printf("Sum value is now: %d\n\r", sum);
	printf("First value is now: %d\n\r", first);
	printf("Last value is now: %d\n\r", last);
	
	/* now check if sum == (first + last) and print YES or NO */
	if (sum == (first + last))
		printf("YES\n\r");
	else
		printf("NO\n\r");
	
	return 0;
}


