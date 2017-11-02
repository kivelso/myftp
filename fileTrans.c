#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define bytesRW 8192

int getClient(char * fileName, int sd)
{
	int bytesWritten, bytesRead, fd;
	char buffer[bytesRW], *p;
	
	if((fd = open(fileName, O_WRONLY)) == -1)// opens file to be read to
	{
		printf("Error: unable to read file.\n");
		exit(1);
	}
	
	while(1)//loops through until socket has been fully read from
	{
		if((bytesRead = read(sd, buffer, sizeof(buffer))==-1))
		{
			printf("Error: unable to read file.\n");
			exit(1);
		}
	
		if(bytesRead == 0) //exits loop as socket has been fully read from
			break;
		
		*p = buffer;

		while(bytesRead>0)
		{
			if((bytesWritten = write(fd, p, bytesRead)) == -1)
			{
				printf("Error: cannot write full string.\n");
				exit(1);
			}
			
			bytesRead-=bytesWritten;
			p+= bytesWritten;
		}
	}

	close(fd);
	exit(0);
}

int getServer(char * fileName, int sd)
{
	int fd, bytesRead, bytesWritten;

	char buffer[bytesRW], *p;
	
	if( (fd= open(fileName, O_RDONLY)) == -1) // opens file to be read from
	{
		printf("Error: unable to open file\n");
		exit(1);
	}
	
	while(1) //loops through until file fully read through
	{
		if((bytesRead = read(fd, buffer, sizeof(buffer))) == -1) 
		{
			printf("Error: unable to read file");
			exit(1);
		}
	
		if(bytesRead == 0)//exits loop as eof has been reached
			break;
		
		*p = buffer;// points p to character array buffer which contains read bytes

		while(bytesRead>0) //loops until read bytes fully written to socket
		{
			if((bytesWritten = write(sd, p, bytesRead)) == -1)
			{
				printf("Error: Write failed.\n");
				exit(1);
			}
			
			bytesRead-=bytesWritten;
			p+= bytesWritten;
		}
	}
	close (fd);
	exit(0);
}

int putClient(char * fileName, int sd)
{
	int bytesRead, bytesWritten, fd;
	char buffer[bytesRW], *p;//buffer for containing read bytes
	
	if(( fd = open(fileName, O_RDONLY)) == -1);//opens file to be read in to
	{
		printf("Error: File failed to open.\n");
		exit(1);
	}
	
	while(1)//loop until file fully read through
	{
		if((bytesRead = read(fd, buffer, sizeof(buffer))) == -1)
		{
			printf("Error: failed write.\n");
			exit(1);
		}
		
		if(bytesRead == 0)//exits loop as eof has been reached
			break;
		
		*p = buffer;// points p to character array buffer which contains read bytes

		while(bytesRead>0)//loops until buffer fully written to socket
		{
			if((bytesWritten = write(sd, p, bytesRead)) == -1)
			{
				printf("Error: unable to write to file.\n");
				exit(1);
			}
			
			bytesRead-=bytesWritten;
			p+= bytesWritten;
		}
	}

	close (fd);
	return 0;
}

int putServer(char * fileName, int sd)
{
	int bytesRead, bytesWritten, fd;
	char buffer[bytesRW], *p;

	if((fd = open(fileName, O_WRONLY)) == -1)//opens file to be written to
	{
		printf("Error: could not open file.\n");
		exit(1);
	}

	while(1)// loop until socket fully read through
	{
		if((bytesRead = read(sd, buffer, sizeof(buffer))) == -1)
		{
			printf("Error: could not read from file.\n");
			exit(1);
		}

		if(bytesRead == 0)// exits loop if nothing left to read from socket
			break;

		*p = buffer;// points p to character array buffer which contains read bytes

		while(bytesRead>0)// loops until read files fully written to file
		{
			if ((bytesWritten = write(fd, p, bytesRead)) == -1)
			{
				printf("Error: write failed.\n");
				exit(1);
			}
			
			bytesRead-=bytesWritten;
			p+=bytesWritten;
		}
	}

	close(fd);
	return 0;
}
