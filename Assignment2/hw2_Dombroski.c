#include <stdio.h>
#include <stdlib.h>

#define BLOCK 64

typedef struct {
  char note[2];
  int duration;
} NOTE;

char *parseNote(int n);

int main (int argc, char[] argv) {
  char notes[][] = {'1', '2', '3', '4', '5', '6', '7', 'i^'};  // available notes on the C major scale
  time_t t;  // variable to hold system time that will seed the random number gen
  int voiceLeadingFlag = 1;
  int melodyCounter = 0;
  int melodySize = BLOCK;  // keeps track of the size of the melody
  int n = 1; // multipicator for melodySize
  int note;
  int dur;
  srand((unsigned) time(&t));  // seed rand

  // declare block of struct pointers
  NOTE **Melody = malloc(BLOCK * sizeof(*NOTE));

  // allocate first C note at beginning of Melody
  Melody[0] = malloc(sizeof(NOTE));
  Melody[0]->note = 'C';
  Melody[0]->duration = (rand()%(3-1))+1;

  // loop executes until a D-C or B-c transition occurs
  while (voiceLeadingFlag == 1) {
    melodyCounter++;
    // check if more memory is needed
    if (melodyCounter == n*BLOCK) {
      n++;
      Melody = realloc(Melody, n*BLOCK*sizeof(*NOTE));
    }
    note = (rand()%(8-1))+1;
    // Check for avoid conditions
    // check for leading voice conditions
    Melody[melodyCounter] = malloc(sizeof(NOTE));
    Melody[melodyCounter]->note = parseNote(note);
    Melody[melodyCounter]->duration = (rand()%(3-1))+1;
  }

  // print out the melody 
  for (int i = 0; i < melodyCounter; i++) {

  }
}

char *parseNote(int n) {
  char *note;
  switch (n) {
    case 1:
      *note = "1";
      break;
    case 2:
      *note = "2";
      break;
    case 3:
      *note = "3";
      break;
    case 4:
      *note = "4";
      break;
    case 5:
      *note = "5";
      break;
    case 6:
      *note = "6";
      break;
    case 7:
      *note = "7";
      break;
    case 8:
      *note = "1^";
      break;
    default:
      break;
  }
  return note;
}
