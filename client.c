#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>       /* struct sockaddr_in, htons, htonl */
#include  <netdb.h>            /* struct hostent, gethostbyname() */
#include  <string.h>
#include  <stdio.h>

#define   SERV_TCP_PORT  40004 /* server's "well-known" port number */
#define   BUFSIZE        (1024*256)


main(int argc, char *argv[])
{
    int sd, n, nr, nw, i=0;
     char host[60];
     struct sockaddr_in ser_addr; struct hostent *hp;

     //Requirement- localhost or other server

     /* get server host name */
     if (argc==1)  /* assume server running on the local host */
         gethostname(host, sizeof(host));
     else if (argc == 2) /* use the given host name */
         strcpy(host, argv[1]);
     else {
         printf("Usage: %s [<server_host_name>]\n", argv[0]); exit(1);
     }


     /* get host address, & build a server socket address */
     bzero((char *) &ser_addr, sizeof(ser_addr));
     ser_addr.sin_family = AF_INET;
     ser_addr.sin_port = htons(SERV_TCP_PORT);
     if ((hp = gethostbyname(host)) == NULL){
           printf("host %s not found\n", host); exit(1);
     }
     ser_addr.sin_addr.s_addr = * (u_long *) hp->h_addr;


        /* create TCP socket & connect socket to server address */
     sd = socket(PF_INET, SOCK_STREAM, 0);
     if (connect(sd, (struct sockaddr *) &ser_addr, sizeof(ser_addr))<0) {
          perror("client connect"); exit(1);
     }




	//not needed with dans work


    //string size tbd
    char input[100];

    int isArgument = 0;

    char argument[100];

    char directory[100];

    int arLen, dirLen;

    while(++i){


        printf(">");
	
	fgets(input,25,stdin);

	if (input[nr-1] == '\n') input[nr-1] = '\0';
          nr = strlen(input);

	//for every char in input
	for(int j = 0; j <= nr;j++){
		//if char is whitespace
		if((input[j] == ' ') || (input[j] == '\t')){

			isArgument = 1;
		}
		else
		{
			if(isArgument == 0){
				strcat(argument,input[j]);		
			}
			if(isArgument == 1){
				strcat(directory,input[j]);
			}
		}

	}

	//lowercase argument
	if (argument[nr-1] == '\n') argument[nr-1] = '\0';
	arLen = strlen(argument);

	for(
	

        //check input if has space
        //iterate first part of input
	//lowercase first part
        //use first part for checks

        //probs should turn into a switch
        if(strcmp(input,"pwd") == 0){
            //pwd command
        }
        else if(strcmp(input,"lpwd") == 0){
            //lpwd command
        }
         else if(strcmp(input,"dir") == 0){
            //dir command
        }
        else if(strcmp(input,"ldir") == 0){
            //pwd command
        }
        else if(strcmp(input,"cd") == 0){
            //cd command
        }
        else if(strcmp(input,"lcd") == 0){
            //lcd command
        }
        else if(strcmp(input,"get") == 0){
            //get command
        }
        else if(strcmp(input,"put") == 0){
            //put command
        }
        else if(strcmp(input,"Quit") == 0){
            //quit command
            exit(0);
        }
        else{
            printf("unkown command: %s\n",input);
        }
				


    }

}
