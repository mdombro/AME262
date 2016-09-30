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
  //char notes[][] = {'1', '2', '3', '4', '5', '6', '7', 'i^'};  // available notes on the C major scale
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

    // Generate random note
    note = (rand()%(9-1))+1;
    // Check for avoid conditions

    // check for leading voice conditions
    if ((strcmp(Melody[melodyCounter-1]->note, "2  ") == 0 && note == 1) || (strcmp(Melody[melodyCounter-1]->note, "7  ") == 0 && note == 8)) {
      voiceLeadingFlag = 0;
    }

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
