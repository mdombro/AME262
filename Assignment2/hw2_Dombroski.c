#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char note[2];
  int duration;
} NOTE;

int main (int argc, char[] argv) {
  char notes[][] = {'1', '2', '3', '4', '5', '6', '7', 'i^'};  // available notes on the C major scale
  time_t t;  // variable to hold system time that will seed the random number gen
  srand((unsigned) time(&t));  // seed rand


}
