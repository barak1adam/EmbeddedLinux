/*
* Hello World program
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char exp[1024] = {};
    if (argc > 1)
    	snprintf(exp, sizeof(exp) - 1, "sed -i '/^Kexalgorithms +diffie-hellman-group1-sha1/s/^/#/' tmp");
    else
	snprintf(exp, sizeof(exp) - 1, "sed -i '/^#Kexalgorithms +diffie-hellman-group1-sha1/s/#//' tmp");

    int rc = system(exp);
    if (-1 == rc && ECHILD == errno) {
	    //sigchld_handler took the signal, no way to detect the real return code. Lets assume it was ok
	    rc = 0;
     }
     if (-1 == rc)
	printf("%s\n",strerror(errno));
     else
        rc = WEXITSTATUS(rc);
	
    return 0;
}
