#include "functions.h"

/*If you have never seen an enum here is a decent artical that discribes what an
 enum is.
https://www.simplilearn.com/tutorials/c-tutorial/enum-in-c#:~:text=Enumeration%20or%20Enum%20in%20C,same%20or%20even%20different%20programmer.
 Quick definition from the above website.
 Enumeration or Enum in C is a special kind of data type defined by the user. It
 consists of constant integrals or integers that are given names by a user. The use
 of enum in C to name the integer values makes the entire program easy to learn,
 understand, and maintain by the same or even different programmer.
 
 While the example does not seem to be a meaningful example there are valid uses of 
 enumerations*/
enum months{JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

const char* monthName[] = {"", "January", "February", "March", "April", 
                               "May", "June", "July", "August", "September",
                               "October", "November", "December"};

void printMonths(FILE* out)
{
    
    enum months m;
    for(m = JAN; m <= DEC; m++)
    {
        fprintf(out, "%2d%12s\n", m, monthName[m]);
    }
}
