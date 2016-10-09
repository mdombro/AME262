#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLOCK 10
#define MAXSIZE 40

typedef struct {
  float t;
  float amp;
} BREAKPOINT;

int main(int argc, char* argv[]) {
    //*************************************************//
    //          Variable declarations section          //
    FILE *fp = NULL;
    char line[BLOCK];
    int n = 1;                  // number of BLOCKs for breakpoint storage
    float in1, in2;
    int read_error = 0;         // checks if sscanf fails on compare
    int flag = 1;
    int breakCounter = 0;
    int file_error;

    //*************************************************//
    //                 Program section                 //
    if (argc < 2) {
        printf("Sorry, please input a filename\n");
        return 1;
    }
    if (argc > 2) {
        printf("Sorry, you have too many arguments. Which is the filename?\n");
        return 1;
    }
    else {
        fp = fopen(argv[1], "w");
        if (fp == NULL) {
          printf("Sorry could not open the file requested!!\n");
          perror("");
        }
    }

    // Create breakpoints structure with a starting size
    BREAKPOINT **points = malloc(BLOCK * sizeof(BREAKPOINT*));

    printf("Breakpoint: Output breakpoints to a text file.\nRulse:\n1. The first number gives the time for the breakpoint, the second number gives the value at that time.\n2. The time of the first point must be 0.\n3. The times must be increasing.\n4. Two breakpoints cannot have the same time.\n5. A breakpoint file must contain at least two points.\n");
    printf("Enter the first breakpoint (time must be 0) (q to exit): ");
    fgets(line, MAXSIZE, stdin);
    printf("%s", line);
    if (strcmp(line, "q\n") == 0) {
        printf("No breakpoints written, exiting\n");
        return 0;
    }
    read_error = sscanf(line, "%f %f", &in1, &in2);
    if (read_error == 0) {
        printf("Wrong input!\n");
        read_error = 0;
    }
    else if (in1 != 0) {
        printf("The first time input must be 0!\n");
        return 1;
    }
    points[0] = malloc(sizeof(BREAKPOINT));
    points[0]->t = in1;
    points[0]->amp = in2;

    while (flag) {
        printf("Enter breakpoint (q to exit): ");
        fgets(line, MAXSIZE, stdin);
        if (strcmp(line, "q\n") == 0) {
            flag = 0;
            if (breakCounter == 0) {
                printf("You only entrede one breakpoint\nNo file will be written\n");
            }
            continue;
        }
        read_error = sscanf(line, "%f %f", &in1, &in2);
        if (read_error == 0) {
            printf("Wrong input!\n");
            continue;
        }
        // check time is increasing and also increment breakCounter
        if (in1 <= points[++breakCounter-1]->t) {
            printf("Time must be increasing\n");
            breakCounter--;      // breakpointer was invalid
            continue;
        }
        // check to see if we need more memory
        if (breakCounter == n*BLOCK) {
            n++;
            points = realloc(points, n*BLOCK*sizeof(BREAKPOINT*));
        }
        points[breakCounter] = malloc(sizeof(BREAKPOINT));
        points[breakCounter]->t = in1;
        points[breakCounter]->amp = in2;
    }

    for (int i = 0; i < breakCounter+1; i++) {
        file_error = fprintf(fp, "%f    %f\n", points[i]->t, points[i]->amp);
        if (file_error < 0) {
            perror("There was an error writing the file!\n");
            break;
        }
    }

    if (file_error > 0) {
        printf("%d breakpoints were written to %s\n", breakCounter+1, argv[1]);
    }

    fclose(fp);

    for (int i = 0; i < breakCounter+1; i++) {
        free(points[i]);
    }
    free(points);

    return 0;
}
