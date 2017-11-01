/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: Myftp client main
**/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>       //struct sockaddr_in, htons, htonl
#include <netdb.h>            //struct hostent, gethostbyname()
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "tokenise.c"
#include "fileTrans.c"

//probably need to be able to change this somehow?
const int SERV_TCP_PORT = 40004; /* server's "well-known" port number */
const int BUFF_SIZE = 1024;

void Tokenise(char[], char**);
void Execute(char**);
void DeamonExecute(char**);



int main(int argc, char **argv){
	int sd, n, nr, nw, i=0;
    char host[60];
    struct sockaddr_in ser_addr; struct hostent *hp;

    //Requirement- localhost or other server

    //get server host name
    if(argc==1){  //assume server running on the local host
        gethostname(host, sizeof(host));
    }else if(argc == 2){ //use the given host name
        strcpy(host, argv[1]);
    }else{
        printf("Usage: %s [<server_host_name>]\n", argv[0]); exit(1);
    }


    //get host address, & build a server socket address
    bzero((char *) &ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SERV_TCP_PORT);
    if ((hp = gethostbyname(host)) == NULL){
        printf("host %s not found\n", host); exit(1);
    }
    ser_addr.sin_addr.s_addr = * (u_long *) hp->h_addr;


    // create TCP socket & connect socket to server address
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if(connect(sd, (struct sockaddr *) &ser_addr, sizeof(ser_addr))<0){
        perror("client connect"); exit(1);
    }


//end dirty copy paste from other file, probs need to integrate better/ split off into functions


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
		for(i=0; 1<BUFF_SIZE; i++){
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
			Tokenise(buffer, args);

		if(*args == "ldir" ||
		   *args == "lpwd" ||
		   *args == "lcd")
		{
			//Execute the command locally.
			Execute(args);
		}else if(*args == "dir" ||
				 *args == "pwd" ||
				 *args == "cd"  ||
				 *args == "put" ||
				 *args == "get")
			//Execute the command remotely.
			DeamonExecute(args);
		}else{
			printf("ERROR: Unknown command!");
		}
    }
}

/*****************************
 * spawn a child process and
 *       Execute the program.
 * Param: args: 1st is the program to run.
 *        The rest are program arguments
 *****************************/
void Execute(args)
char **args;
{
    int pid, status;

    //Get a child process.
    if ((pid = fork()) < 0){
        perror("fork");
		//Flag failure to execute
        exit(1);

		/* NOTE: perror() produces a short  error  message  on  the  standard
           error describing the last error encountered during a call to
           a system or library function. */
    }

    //The child Executes the code inside the if.
    if (pid == 0){
		//Effectively redirect stdout to the file, file will be created in not existent
		freopen("output.txt", "a+", stdout); 
        execvp(*args, args);
        perror(*args);
		//Do stuff with the output redirection????-maybe fopen and do stuff after restoring stdout
		//Reset stdout - Unix specific
		freopen("/dev/tty", "w", stdout);
		//Clean exit the child
        exit(0);
    }

    //The parent Executes the wait.
    while (wait(&status) != pid)
        /* empty */ ;
}

/*********************************
 * Send the request to the server and await response
 * Param: args: 1st is the program to run.
 *        The others are program arguments.
 ********************************/
void DeamonExecute(args)
char **args;
{
    //DO NETWORKING THINGS
	
	/*Pseudo
	if("get"){
		getClient(args, num);
	}else if("put"){
		putClient(args, num);
	}else if("dir"){
		//send dir command to server
	}else if("pwd"){
		//send pwd command to server
	}else if("cd"){
		//semd cd command to server
	}else{
		printf("ERROR: Unknown command!");
	}
	END Pseudo*/
}

















    /*This was an experiment, mostly worked
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
