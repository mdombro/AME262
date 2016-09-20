// Listing 12.14: dyn_arr.c
// dynamically allocated array
#include <stdio.h>
#include <stdlib.h> // for malloc(), free()

int main(void)
{
    double * ptd;
    int max;
    int number;
    int i = 0;

    puts("What is the maximum number of type double entries?");
    if (scanf("%d", &max) != 1)
    {
        puts("Number not correctly entered -- bye.");
 //       printf("EXIT_FAILURE = %d\n", EXIT_FAILURE);
        exit(EXIT_FAILURE);   // EXIT_FAILURE == 1
    }
    //  use malloc() here for dynamic memory allocation
    
    
    
    // "memory allocation failed" condition
    
    
    
    /* ptd now points to an array of max elements */

    puts("Enter the values (q to quit):");
    while (i < max && scanf("%lf", &ptd[i]) == 1)  // ptd + i
        ++i;
    printf("Here are your %d entries:\n", number = i);
    for (i = 0; i < number; i++)
    {
        printf("%-7.2f ", ptd[i]);
        if (i % 7 == 6)
            putchar('\n');
    }
    if (i % 7 != 0)
        putchar('\n');
    puts("Done.");
    free(ptd);

    return 0;
}
