#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLOCK 64

typedef struct {
  float t;
  float amp;
} BREAKPOINT;

int main(int argc, char* argv[]) {
    //*************************************************//
    //          Variable declarations section          //
    FILE *fp = NULL;

    //*************************************************//
    //                 Program section                 //
    if (argc < 2) {
        printf("Sorry, please input a filename");
    }
    if (argc > 2) {
        printf("Sorry, you have too many arguments. Which is the filename?");
    }
    else {
        fp = fopen(argv[1], "w");
        if (fp == NULL) {
          printf("Sorry could not open the file requested!!\n");
          perror("");
        }
    }

    // Create breakpoints structure with a starting size
    BREAKPOINT **points = malloc(BLOCK * sizeof(BREAKPIONT*));

    printf("Breakpoint: Output breakpoints to a text file.\nRulse:\n1. The first number gives the time for the breakpoint, the second number gives the value at that time.\n2. The time of the first point must be 0.\n3. The times must be increasing.\n4. Two breakpoints cannot have the same time.\n5. A breakpoint file must contain at least two points.\n");

    while () {
        
    }
}
