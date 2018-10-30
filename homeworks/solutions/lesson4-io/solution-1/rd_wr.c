#include "lesson4-1.h"

/******************************************************************************************/
//Globals
/******************************************************************************************/

/*******************************************************************************/	
	/* Writes LENGTH bytes from BUFFER into a temporary file. The
	temporary file is immediately unlinked. Returns a handle to the
	temporary file. */
	temp_file_handle write_temp_file (int fileName, char* wrBuffer, size_t length)
	{
		ssize_t len;
		int fd = fileName;
	
		/* Now write the data itself. */
		len = write (fd, wrBuffer, length);
		if(len == -1)
		{
	  	    perror("write");
	   	    return (-1);
		}	
		return len;
	}
/*******************************************************************************/
	/* Reads the contents of a temporary file TEMP_FILE created with
	write_temp_file.
	*LENGTH is set to the size of the contents, in bytes. */

//	void read_temp_file (int fileName, char* rdBuffer, size_t length)
	char* read_temp_file (int fileName, size_t length)
	{
		char *buffer = NULL;
		size_t len;
		
		/* The TEMP_FILE handle is a file descriptor to the temporary file. */
		int fd = fileName;

		/* Rewind to the beginning of the file. */
//		lseek (fd, 0, SEEK_SET);
		buffer = (char*) malloc (length);
		{
			if (buffer == NULL)
			exit(-1);
		}
		len = read (fd, buffer, length);
		if(len == -1)
		{
	  	    perror("read");
		    return (char*) NULL;
		}
//		printf("%s\n",buffer);
		return buffer;			
	}
/*******************************************************************************/

