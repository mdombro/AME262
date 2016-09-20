/*  Homework: You don't need to submit yours to Blackboard;
 however, you may show your program to the class on Thursday, 9/13.
 interval.c: (from The Audio Programming Book, pp.17-19
 Calculate the interval between two natural notes
 and prints its semitone length and name.
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
    char note1, note2; // note names, dummy char
    int pc1, pc2, interval;   // pitch classes, interval
                          // A   B   C   D   E   F   G
    int intervals[7][7] = { {0,  10, 9,  7,  5,  4,  2},   // A
                            {2,  0,  11, 9,  7,  6,  4},   // B
                            {3,  1,  0,  10, 8,  7,  5},   // C
                            {5,  3,  2,  0,  10, 9,  7},   // D
                            {7,  5,  4,  2,  0,  11, 9},   // E
                            {8,  6,  5,  3,  1,  0,  10},  // F
                            {10, 8,  7,  5,  3,  2,  0}};  // G
    printf("Please enter two natural notes (as capitals).\nFirst note: ");
    // Please complete the program
    while(scanf("%c", &note1) != 1 || (note1 < 'A' || note1 > 'G') || (note1 == ' ')) {
        printf("Wrong input! Input again: ");
        while(getchar() != '\n'){} // clear input buffer
    }
    while(getchar()!='\n');  // clear input buffer
    printf("Second note: ");
    while(scanf("%c", &note2) != 1 || (note2 < 'A' || note2 > 'G') || (note2 == ' ')) {
        printf("Wrong input! Input again: ");
        while(getchar() != '\n'){} // clear input buffer
    }
    note1 -= 'A';  // set note for indexing
    note2 -= 'A';
    printf("%d semitones up or %d semitones down\n", intervals[note2][note1], intervals[note1][note2]);

    return 0;
}

/* sample outputs:
 first note: D
 second note: C
 10 semitones up or 2 semitones down
 minor 7th up or major 2nd down

 Please enter two natural notes.
 first note: F
 second note: F
 0 semitones up or 0 semitones down
 unison
*/
