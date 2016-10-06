/******************************/
/*       Matt Dombroski       */
/*       hw2_Dombroski.c      */
/******************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLOCK 64  // Base size of array size for holding melody
                  // Used to realloc more space as needed

typedef struct {
  char note[5];
  int duration;
} NOTE;  // Every note has a pitch and a duration

char *parseNote(int n);  // for parsing int notes into string versions for printing

int main (int argc, char *argv[]) {
  time_t t;                   // variable to hold system time that will seed the random number gen
  int voiceLeadingFlag = 1;   // voice leading flag condition
  int melodyCounter = 0;      // Keeps track of number of notes generated int he melody
  int melodySize = BLOCK;     // keeps track of the size of the melody
  int n = 1;                  // multipicator for melodySize
  int note;                   // hold the integer version of the generated note
  int dur;                    // Holds duration during printing operation
  int beatCount = 0;          // Keeps track of beats to separate measures
  int measureCount = 0;       // Keeps track of measures to go to new lines
  srand((unsigned) time(&t)); // seed rand
  FILE *fp = NULL;
  int err = 0;                // error tracker for file writing
  int invalid = 1;            // flag for valid note transition

  // Validate optional input file
  if (argc > 2) {
    printf("Too many input arguments!!\n");
    return 1;
  }
  if (argc == 2) {
    fp = fopen(argv[1], "w");
    if (fp == NULL) {
      printf("Sorry could not open the file requested!!\n");
      perror("");
    }
  }

  // declare block of struct pointers
  NOTE **Melody = malloc(BLOCK * sizeof(NOTE*));

  // allocate first C note at beginning of Melody
  Melody[0] = malloc(sizeof(NOTE));
  strcpy(Melody[0]->note, "1  ");
  Melody[0]->duration = (rand()%(4-1))+1;

  // loop executes until a D-C or B-c voice leading transition occurs
  while (voiceLeadingFlag == 1) {
    melodyCounter++;

    // check if more memory is needed
    if (melodyCounter == n*BLOCK) {
      n++;
      Melody = realloc(Melody, n*BLOCK*sizeof(NOTE*));
    }

    // Check for avoid conditions
    // F-B, B-F, C-B, B-C, c-D, D-c, C-c, c-C
    invalid = 1;
    while (invalid) {
      // Generate random note to test
      note = (rand()%(9-1))+1;

      if ( (strcmp(Melody[melodyCounter-1]->note, "4  ") == 0 && note == 7) || (strcmp(Melody[melodyCounter-1]->note, "7  ") == 0 && note == 4) ) {
        invalid=1; continue;
      }
      if ( (strcmp(Melody[melodyCounter-1]->note, "1  ") == 0 && note == 7) || (strcmp(Melody[melodyCounter-1]->note, "7  ") == 0 && note == 1) ) {
        invalid=1; continue;
      }
      if ( (strcmp(Melody[melodyCounter-1]->note, "1^ ") == 0 && note == 2) || (strcmp(Melody[melodyCounter-1]->note, "2  ") == 0 && note == 8) ) {
        invalid=1; continue;
      }
      if ( (strcmp(Melody[melodyCounter-1]->note, "1  ") == 0 && note == 8) || (strcmp(Melody[melodyCounter-1]->note, "1^ ") == 0 && note == 1) ) {
        invalid=1; continue;
      }
      invalid=0;  // if no avoid conditions present move on to next step - checking for voice leading
    }

    // check for leading voice conditions
    if ((strcmp(Melody[melodyCounter-1]->note, "2  ") == 0 && note == 1) || (strcmp(Melody[melodyCounter-1]->note, "7  ") == 0 && note == 8)) {
      voiceLeadingFlag = 0;
    }

    // Allocate and fill out the new Note
    Melody[melodyCounter] = malloc(sizeof(NOTE));
    strcpy(Melody[melodyCounter]->note, parseNote(note));
    Melody[melodyCounter]->duration = (rand()%(4-1))+1;
  }

  // print out the melody
  for (int i = 0; i < melodyCounter+1; i++) {
    printf("%s", Melody[i]->note); beatCount++;
    if (beatCount == 4) {printf("|  "); beatCount = 0; measureCount++;}
    if (measureCount == 4) {printf("\n"); measureCount = 0;}
    dur = Melody[i]->duration;
    while (--dur > 0) {  // pre-decrement so a one beat note has no '-  '
      printf("-  "); beatCount++;
      if (beatCount == 4) {printf("|  "); beatCount = 0; measureCount++;}
      if (measureCount == 4) {printf("\n"); measureCount = 0;}
    }
  }
  if (beatCount != 0) printf("|\n");
  else printf("\n");

  // Print melody to the file if given
  if (fp != NULL) {  // check if there was a file argument
    beatCount  = 0;
    measureCount = 0;
    for (int i = 0; i < melodyCounter+1; i++) {
      err = fprintf(fp, "%s", Melody[i]->note); beatCount++;
      if (beatCount == 4) {err = fprintf(fp, "|  "); beatCount = 0; measureCount++;}
      if (measureCount == 4) {err = fprintf(fp, "\n"); measureCount = 0;}
      dur = Melody[i]->duration;
      while (--dur > 0) {  // pre-decrement so a one beat note has no '-  '
        err = fprintf(fp, "-  "); beatCount++;
        if (beatCount == 4) {err = fprintf(fp, "|  "); beatCount = 0; measureCount++;}
        if (measureCount == 4) {err = fprintf(fp, "\n"); measureCount = 0;}
      }
      if (err < 0) {break;}
    }
    if (beatCount != 0) err = fprintf(fp, "|\n");
    else err = fprintf(fp, "\n");
  }

  // Last error check for the file writing
  if (err < 0) {
    perror("There was an error writing the file!\n");
  }

  // If there was a file, close it
  if (fp != NULL) {
    fclose(fp);
  }

  // free the structs then the array of pointers to the structs
  for (int i = 0; i < melodyCounter+1; i++) {
    free(Melody[i]);
  }
  free(Melody);

  return 0;
}

// take the int and return a string version with some formatting built in
char *parseNote(int n) {
  char *note;
  note = malloc(4);
  switch (n) {
    case 1:
      strcpy(note, "1  ");
      break;
    case 2:
      strcpy(note, "2  ");
      break;
    case 3:
      strcpy(note, "3  ");
      break;
    case 4:
      strcpy(note, "4  ");
      break;
    case 5:
      strcpy(note, "5  ");
      break;
    case 6:
      strcpy(note, "6  ");
      break;
    case 7:
      strcpy(note, "7  ");
      break;
    case 8:
      strcpy(note, "1^ ");
      break;
    default:
      break;
  }
  return note;
}
