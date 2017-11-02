/**
 * Author: Daniel Coughran
 * Date: 01/11/2017
 * Purpose: Tokenise an input string 
 * (convert white-space to nulls)
**/


/*******************************
 * split the command in buf into
 *         individual arguments.
 *******************************/
 //Testing an idea, if next line errs, remove stars
void Tokenise(char *buffer, char **args)
//char *buffer;
//char **args;
{
    while (*buffer != NULL){
        /*
        * Strip white-space.  Use nulls, so that the 
		* previous argument is terminated automatically.
        */
        while ((*buffer == ' ') || (*buffer == '\t') || (*buffer == '\n'))
            *buffer++ = NULL;

        //Save the argument.
        *args++ = buffer;

        //skip over the argument.
        while ((*buffer != NULL) && (*buffer != ' ') && (*buffer != '\t'))
            buffer++;
    }
    *args = NULL;
}