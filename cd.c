/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: encapsulate cd function, could be extended
 *          with related functionality if needed
**/

#include <stdlib.h>
#include <stdio.h>

void DoDir(char* dir){
    printf("hit cd\n");
    system("cd %s", "Fuck this part doesnt work");
    return;
}

/*int main()
{
    //printf("files in directory are:\n");
	DoDir();
	return(0);
}*/
