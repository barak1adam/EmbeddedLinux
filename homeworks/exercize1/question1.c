	if ( (fd = open("/home/mrv/mrv", O_RDONLY | O_CREAT, 0666)) < 0 )
	{
		perror("failed to open /home/mrv/mrv");
		exit(errno);
	}
