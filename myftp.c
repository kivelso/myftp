/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: Myftp client main
**/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
//#include "pwd.c"
//#include "dir.c"
//#include "cd.c"

const int BUFF_SIZE = 1024;

//void DoPWD();
//void DoDir();
//void DoCd();

void parse(char[], char**);
void execute(char**);
void deamonExecute(char**);

int main(int argc, char **argv){
    char buffer[BUFF_SIZE];
    char *args[512];

    printf("Type quit to exit.\n");
    //loop forever, exit() call within loop
    while(1){
        //Prompt for and read a command.
        printf(">");

	fgets(buffer, BUFF_SIZE, stdin);
	int i;
	//strip newline then break
	for(i=0;1<BUFF_SIZE; i++){
	    if(buffer[i] == '\n'){
		buffer[i] = '\0';
		break;
	    }
	}
        //exit on "quit"
        if (strcmp(buffer, "quit") == 0){
            printf("\n");
            exit(0);
        }

        //Split the string into arguments.
        parse(buffer, args);

	if(*args == "ldir" ||
	   *args == "lpwd" ||
 	   *args == "lcd")
	{
	    execute(args);
	}else{//dir||pwd||cd||put||get
            deamonExecute(args);
	}

	 //Execute the command.
         //execute(args);
    }
}


/*******************************
 * split the command in buf into
 *         individual arguments.
 *******************************/
void parse(buffer, args)
char *buffer;
char **args;
{
    while (*buffer != NULL){
        /*
        * Strip whitespace.  Use nulls, so
        * that the previous argument is terminated
        * automatically.
        */
        while ((*buffer == ' ') || (*buffer == '\t'))
            *buffer++ = NULL;

        //Save the argument.
        *args++ = buffer;

        //skip over the argument.
        while ((*buffer != NULL) && (*buffer != ' ') && (*buffer != '\t'))
            buffer++;
    }

    *args = NULL;
}

/*****************************
 * spawn a child process and
 *       execute the program.
 * Param: args: 1st is the program to run.
 *        The rest are program arguments
 *****************************/
void execute(args)
char **args;
{
    int pid, status;

    //Get a child process.
    if ((pid = fork()) < 0){
        perror("fork");
        exit(1);

	/* NOTE: perror() produces a short  error  message  on  the  standard
           error describing the last error encountered during a call to
           a system or library function. */
    }

    //The child executes the code inside the if.
    if (pid == 0){
        execvp(*args, args);
        perror(*args);
        exit(1);

    }

    //The parent executes the wait.
    while (wait(&status) != pid)
        /* empty */ ;
}

/*********************************
 * Send the request to the server and await response
 * Param: args: 1st is the program to run.
 *        The others are program arguments.
 ********************************/
void deamonExecute(args)
char **args;
{
    //DO NETWORKING THINGS
}

















    /*
    int i = 0;
    for (i = 0; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);

        //not strcmp as it returns 0 when equal
        if(!strcmp(argv[i],"pwd")){
            printf("is pwd\n");
            DoPWD();
            printf("\n");

        //not strcmp as it returns 0 when equal
        }else if(!strcmp(argv[i],"dir")){
            printf("is dir\n");
            DoDir();
            printf("\n");
        }

        //not strcmp as it returns 0 when equal
        }else if(!strcmp(argv[i],"cd")){
            printf("is cd\n");
            DoCd(argv[i+1]);
            printf("\n");
        }
    }
    return(0);
}*/
