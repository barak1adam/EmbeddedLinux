#include <stdio.h>
#include <string.h>

/* I suggest you to play with getchar, scanf, printf functions to understand how they 
   handle values */
int x = 100000000;

void print_many_words()
{
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	printf("biskiiiiiiiiiiiiiiiiiii\n\r");
	return;
}

int add_x_y(int a, int b)
{
	int ret_value = 0;
	printf("x inside function add_x_y = %d\n\r", x);
	ret_value = a + b;
	return ret_value;
}
char add_char_x_y(char a, char b)
{
	char ret_value = 0;
	//int x = 5000;
	ret_value = a + b;
	return ret_value;
}

int main(int argc, void **argv)
{
 
 /* Bishki - getchar is used to get the char values as entered on keyboard, like '1', '2', 'a', 'b'...
      The exact value you'll get is actually a special number (ASCII) used to represent the character
	  for example:
	  char c = getchar();
	  if you enter 'a' on the keyboard, c will get the (ASCII) value that represnets 'a' which is 97 
	  so if you are using getchar you always have the char values ...
	  If you like to convert (format) the input/output to other values like integers, double, strings, then
	  you can use functions like scanf, printf, etc... (f=format)*/

	if (5)
		printf("\"argc = %d\"\n\r", argc);
	char buf[100] = {0};
	int dev_name_len = (int)( strrchr((char *)argv[2], '_') - strchr((char *)argv[2], '_') -1);
	printf("argv[2] = %s\n\r", (char *)argv[2]);
	strncpy(buf, strchr( (char *)argv[2], '_')+1, dev_name_len );
	printf("dev name = %s\n\r", buf);
	printf("first= %s\n\r", strchr( (char *)argv[2], '_'));
	printf("last= %s\n\r", strrchr( (char *)argv[2], '_'));
	printf("length = %d\n\r", (int)( strrchr((char *)argv[2], '_') - strchr((char *)argv[2], '_') -1));

#if 0
	char c;
	int x,y,ret;

   
	printf("Enter x and y values:");
	ret = scanf("%d %d", &x, &y);
	printf("\nx and y values entered: %d, %d\n\r", x, y);
	printf("ret = %d\n\r", ret);

	printf("Enter a value:");
	ret = scanf(" %c", &c);
	printf("c = %c\n\r", c);
	printf("ret = %d\n\r", ret);

	//now call noa(x,y,c)...
#endif
	return 0;
}
