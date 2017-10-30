/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: Myftp client main
**/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "pwd.c"
#include "dir.c"
#include "cd.c"

void DoPWD();
void DoDir();
void DoCd();

int main(int argc, char **argv){
    char buffer[1024];
    char *args[512];

    printf("Type EXIT to exit.\n");
    while(1){
        //Prompt for and read a command.
        printf("Enter command: ");

        if (gets(buffer) == NULL) {
            printf("\n");
            exit(0);
        }

        //Split the string into arguments.
        parse(buffer, args);

        //Execute the command.
        execute(args);
    }
}


/*******************************
 * split the command in buf into
 *         individual arguments.
 *******************************/
parse(buffer, args)
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
 *****************************/
execute(args)
char **args;
{
    int pid, status;

    /*
     * Get a child process.
     */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);

	/* NOTE: perror() produces a short  error  message  on  the  standard
           error describing the last error encountered during a call to
           a system or library function.
       */
    }

    /*
     * The child executes the code inside the if.
     */
    if (pid == 0) {
        execvp(*args, args);
        perror(*args);
        exit(1);

       /* NOTE: The execv() vnd execvp versions of execl() are useful when the
          number  of  arguments is unknown in advance;
          The arguments to execv() and execvp()  are the name
          of the file to be executed and a vector of strings  contain-
          ing  the  arguments.   The last argument string must be fol-
          lowed by a 0 pointer.

          execlp() and execvp() are called with the same arguments  as
          execl()  and  execv(),  but duplicate the shell's actions in
          searching for an executable file in a list  of  directories.
          The directory list is obtained from the environment.
        */
    }

    /*
     * The parent executes the wait.
     */
    while (wait(&status) != pid)
        /* empty */ ;
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
