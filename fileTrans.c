#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/socket>
#include <sys/types>

int getClient(char * fileName, int sd)
{
	int bytesWritten, bytesRead;
	char * buffer, *p;
	fd = open(fileName, O_WRONLY);


	while(1)
	{
		
		bytesRead = read(sd, buffer, sizeof(buffer));
	
		if(bytesRead = 0)
			break;
		
		if(bytesRead < 0){
			//error handling
		}
		
		*p = buffer;

		while(bytesRead>0)
		{
			bytesWritten = write(fd, p, bytesRead);
			
			if(bytesWritten <=0){
				//handle errors
			}
			
			bytesRead-=bytesWritten
			p+= bytesWritten;
		}
	}

	close(fd);
	return 0;
}

int getServer(char * fileName, int sd)
{
	fd = open(fileName, O_RDONLY);

	char * buffer, *p;
	
	int bytesRead, bytesWritten;

	while(1)
	{
		
		bytesRead = read(fd, buffer, sizeof(buffer));
	
		if(bytesRead = 0)
			break;
		
		if(bytesRead < 0)
		{
			//error handling
		}
		
		*p = buffer;

		while(bytesRead>0)
		{
			bytesWritten = write(sd, p, bytesRead);
			
			if(bytesWritten <=0){
				//handle errors
			}
			
			bytesRead-=bytesWritten;
			p+= bytesWritten;
		}
	}

	close (fd);

	return 0;
}

int putClient(char * fileName, int sd)
{
	fd = open(fileName, O_RDONLY);//opens file to be written to

	char * buffer, *p;//buffer for containing read bytes
	int bytesRead, bytesWritten;

	while(1)
	{
		
		bytesRead = read(fd, buffer, sizeof(buffer));
	
		if(bytesRead = 0)
			break;
		
		if(bytesRead < 0)
		{
			//error handling
		}
		
		*p = buffer;

		while(bytesRead>0)
		{
			bytesWritten = write(sd, p, bytesRead);
			
			if(bytesWritten <=0){
				//handle errors
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
	fd = open(fileName, O_WRONLY);

	char * buffer, *p;

	int bytesRead, bytesWritten;

	while(1)
	{
		bytesRead = read(sd, buffer, sizeof(buffer));

		if(bytesRead = 0)
			break;

		if(bytesRead < 0)
		{
			//error handling
		}

		*p = buffer;

		while(bytesRead>0)
		{
			bytesWritten = write(fd, p, bytesRead);
			
			if(bytesWritten <=0)
			{		
				//handle errors
			}
			
			bytesRead-=bytesWritten;
			b+=bytesWritten;
		}
	}

	close(fd);

	return 0;
}
