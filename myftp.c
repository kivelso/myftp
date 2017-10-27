/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: Myftp client main
**/

#include <stdlib.h>
#include <stdio.h>
#include "pwd.c"
#include "dir.c"
#include "cd.c"

void DoPWD();
void DoDir();

int main(int argc, char **argv){
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
}
