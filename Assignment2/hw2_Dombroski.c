#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLOCK 64

typedef struct {
  char note[5];
  int duration;
} NOTE;

char *parseNote(int n);

int main (int argc, char *argv[]) {
  time_t t;  // variable to hold system time that will seed the random number gen
  int voiceLeadingFlag = 1;
  int melodyCounter = 0;
  int melodySize = BLOCK;  // keeps track of the size of the melody
  int n = 1; // multipicator for melodySize
  int note;
  int dur;
  int beatCount = 0;
  int measureCount = 0;
  srand((unsigned) time(&t));  // seed rand
  FILE *fp = NULL;
  int err = 0; // error tracker for file writing
  int invalid = 1;  // flag for valid note transition

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
  Melody[0]->duration = (rand()%(3-1))+1;

  // loop executes until a D-C or B-c transition occurs
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
      // Generate random note
      note = (rand()%(9-1))+1;

      if ( (strcmp(Melody[melodyCounter-1]->note, "4  ") == 0 && note == 7) || (strcmp(Melody[melodyCounter-1]->note, "7  ") && note == 4) ) {
        invalid=1; continue;
      }
      if ( (strcmp(Melody[melodyCounter-1]->note, "1  ") == 0 && note == 7) || (strcmp(Melody[melodyCounter-1]->note, "7  ") && note == 1) ) {
        invalid=1; continue;
      }
      if ( (strcmp(Melody[melodyCounter-1]->note, "1^ ") == 0 && note == 2) || (strcmp(Melody[melodyCounter-1]->note, "2  ") && note == 8) ) {
        invalid=1; continue;
      }
      if ( (strcmp(Melody[melodyCounter-1]->note, "1  ") == 0 && note == 8) || (strcmp(Melody[melodyCounter-1]->note, "1^ ") && note == 1) ) {
        invalid=1; continue;
      }
      invalid=0;
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
  printf("|\n");

  // Print melody to the file if given
  if (fp != NULL) {
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
    err = fprintf(fp, "|\n");
  }

  if (err < 0) {
    perror("There was an error writing the file!\n");
  }

  if (fp != NULL) {
    fclose(fp);
  }

  return 0;
}

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
