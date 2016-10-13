// hw2.c by MING-LUN LEE
// Algorithmic composition
// There are several ways to complete the program.
// An alternative is to use 'switch' (or if-else) to print the notes.
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the seed

void printNote(int noteNum, int beats, FILE * fp); // return beat number counter
int beatCounter = 1; // track the last beat of the note (between 1 and 4)
int barCounter = 0; // track the bar number per line (between 0 and 3)
char * notes[8]= {"1  ","2  ","3  ","4  ","5  ","6  ","7  ","1^ "}; // eight natural notes

int main(int argc, const char * argv[]) {
    FILE * fp;  // to read the file
    if(argc != 2) // Usage message
    {
        printf("Usage: %s output_text_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if((fp = fopen(argv[1], "w")) == NULL) // fail to open a file for writing
    {
        printf("Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // seed random number generator;
    srand((unsigned)time(NULL));
    
    int dur;   // note duration
    int previousNote, currentNote; // between 0 and 7
    previousNote = 0; // first note Do
    currentNote = 0;  // first note Do
    dur = rand() % 3 + 1;   // between 1 and 3
    printNote(previousNote, dur, fp); //print C4
    do {
        previousNote = currentNote; // update the previous note
        currentNote = rand() % 8;  //update the current note
        if((previousNote == 3 && currentNote == 6)||(previousNote == 6 && currentNote == 3))  // avoid the tri-tone interval
        {
            currentNote = previousNote; // do not update current note
            continue;
        }
        if(abs(previousNote-currentNote) == 6) // avoid major or minor seventh. It is not neccessary to use the abs function.
        {
            currentNote = previousNote; // do not update current note
            continue;
        }
        if (abs(previousNote-currentNote) == 7)
        {
            currentNote = previousNote; // do not update current note
            continue;
        }
        dur = rand() % 3 + 1;
        printNote(currentNote, dur, fp);
    }
    while(!((previousNote == 1 && currentNote == 0)||(previousNote == 6 && currentNote == 7)));  // End the piece with Re-Do or Ti-DO
    if(beatCounter != 1 )  // the last bar line
    {
        printf("|\n");
        fprintf(fp, "|\n");
    }
    else
    {
        putchar('\n');  // new line
        putc('\n', fp);
    }
    
    fclose(fp);
    
    return 0;
}

void printNote(int noteNum, int beats, FILE * fp) // print a note
{
    printf("%s", notes[noteNum]);
    fprintf(fp, "%s", notes[noteNum]);
    if(beatCounter == 4)
    {
        printf("| ");
        fprintf(fp, "| ");
        barCounter++;   // update the bar counter
        barCounter %= 4;
        if(barCounter == 0)
        {
            putchar('\n');   // change to a new line every four bars;
            putc('\n', fp);
        }
    }
    beatCounter = beatCounter % 4 + 1;  // move to the next bar
    while(beats > 1)
    {
        printf("-  ");  // print '-' for the same note
        fprintf(fp, "-  ");
        beats--;
        if(beatCounter == 4)   // print a bar line
        {
            printf("| ");
            fprintf(fp, "| ");
            barCounter++;   // update the bar counter
            barCounter %= 4;   // bar counter is between 0 and 3
            if(barCounter == 0)// change to a new line every four bars
            {
                putchar('\n');
                putc('\n', fp);
            }
        }
        beatCounter = beatCounter % 4 + 1;  // move to the next bar
    }
}