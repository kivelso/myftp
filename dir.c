/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: encapsulate dir function, could be extended
 *          with related functionality if needed
**/

#include <stdlib.h>
#include <stdio.h>

void DoDir(){
    printf("hit dir\n");
    system("dir");
    return;
}

/*int main()
{
    //printf("files in directory are:\n");
	DoDir();
	return(0);
}*/
