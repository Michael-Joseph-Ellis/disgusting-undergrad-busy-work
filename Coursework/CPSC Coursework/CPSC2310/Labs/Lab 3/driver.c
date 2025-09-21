
/*functions.h is where the C std... libraries are defined.*/
#include "src/functions.h"

int main(int argc, char *argv[])
{
    /*Creates and opens a file pointer. The file being opened will be defined on
     the command line. This file will be written to rather than read from. */
    FILE* out = fopen(argv[1], "w");
    
    /*Assert is being used to check tha tthe file opened successfully*/

    assert(out != NULL);
    
    printMonths(out);
    
    /*Any time you open a file you should have a call to fclose to close the file.
     If you do not it could cause a security vulnerability.*/
    fclose(out);
    return 0;
}

