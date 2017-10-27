/**
 * Author: Daniel Coughran
 * Date: 27/10/2017
 * Purpose: encapsulate pwd function, could be extended
 *          with related functionality if needed
**/

#include <stdlib.h>
#include <stdio.h>

void DoPWD(){
    printf("hit pwd\n");
    system("pwd");
    return;
}

/*int main()
{
    //printf("Wroking directory is:\n");
	DoPWD();
	return(0);
}*/
