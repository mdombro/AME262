// hw1_Dombroski.c by Matthew Dombroski

#include <stdio.h>
#include <math.h>
#include <string.h>

void swap(int* v1, int* v2);

int main() {
  char notes[3][3] = {};
  char strnote[3][7] = {"first", "second", "third"}; // input prompt fillers
  char strclasses[][6] = {"C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B"};  // list of possible notes
  int classes[3];  // Holds sorted input notes that are cast into numbers around the note circle

  // accept the input notes
  printf("Enter three notes\nUse capitals, # for sharp, b for flat.\n");
  for (int i = 0; i < 3; i++) {
    printf("Enter %s note: ", strnote[i]);
    while(scanf("%s", &notes[i]) != 1 || (notes[i][0] < 'A' || notes[i][0] > 'G') || !(notes[i][1] == '#' || notes[i][1] == 'b' || notes[i][1] == '\0') ){
        printf("Wrong input! Input again: ");
        while(getchar() != '\n'){} // clear input buffer
    }
  }

  // Recast outliers of E# - F, B# - C, Fb - E, Cb - B
  for (int i = 0; i < 3; i++) {
    if (!strcmp(notes[i], "E#"))
      strcpy(notes[i], "F");
    if (!strcmp(notes[i], "B#"))
      strcpy(notes[i], "C");
    if (!strcmp(notes[i], "Fb"))
      strcpy(notes[i], "E");
    if (!strcmp(notes[i], "Cb"))
      strcpy(notes[i], "B");
  }

  // parse notes into classes
  int class;
  for (int o = 0; o < 3; o++) {
    //printf("%s\n", notes[o]);
    for (int i = 0; i < 12; i++) {
      if (notes[o][1] == '\0' && strclasses[i][2] == '/')  // if the input note is a natural and the compared note has an acidental
        continue;                                          // continue to find the natural note
      if (strstr(strclasses[i], notes[o]) == NULL)  // Check if input note matches anything in the list of notes
        class = 0;
      else {
        class = i; break;
      }
    }
    classes[o] = class;
  }

  // classify triad
  // sort into a starting order
  for (int i = 0; i < 2; i++) {
    for (int o = 0; o < 2-i; o++) {
      if (classes[o] > classes[o+1]) {
        swap(&classes[o], &classes[o+1]);
      }
    }
  }

  // Triad is tested by checking space between the notes and categorizing bsaed on triad rules
  // If the original sorted order does not have a match the first note is placed at the end with 12 added to its note class and the middle
  // note placed at the start of the array. If this order does not work again
  // the last note is placed at the back plus 12 and middle to the front. If this last order does not have a matches
  // the program states no traid is formed
  int flag = 0;  // flag breaks out of loop faster if a match is found
  int temp = 0;
  int testnotes[3];
  // filler keeps track of the present order of the notes so they print in the correct lowest to highest order
  int filler[][3] = {{classes[0], classes[1], classes[2]},
                     {classes[1], classes[2], classes[0]},
                     {classes[2], classes[0], classes[1]}};
  // a placeholder so the actual classes array is not changed
  testnotes[0] = classes[0]; testnotes[1] = classes[1]; testnotes[2] = classes[2];
  for (int i = 0; i < 3; i++) {
    //printf("%d  %d  %d\n", testnotes[0],testnotes[1],testnotes[2]);
    switch (testnotes[2]-testnotes[0]) {
      case 7: {
        if (testnotes[1]-testnotes[0] == 3) {
          printf("%s - %s - %s forms a minor triad\n", strclasses[filler[i][0]], strclasses[filler[i][1]], strclasses[filler[i][2]]);
          flag = 1;
        }
        if (testnotes[1] - testnotes[0] == 4) {
          printf("%s - %s - %s forms a major triad\n", strclasses[filler[i][0]], strclasses[filler[i][1]], strclasses[filler[i][2]]);
          flag = 1;
        }
        break;
      }
      case 6: {
        if (testnotes[1]-testnotes[0] == 3) {
          printf("%s - %s - %s forms a diminished triad\n", strclasses[filler[i][0]], strclasses[filler[i][1]], strclasses[filler[i][2]]);
          flag = 1;
        }
        break;
      }
      case 8: {
        if (testnotes[1]-testnotes[0] == 4) {
          printf("%s - %s - %s forms a augmented triad\n", strclasses[filler[i][0]], strclasses[filler[i][1]], strclasses[filler[i][2]]);
          flag = 1;
        }
        break;
      }
      default:
        break;
    }
    if (flag) break;
    temp = testnotes[0];
    // reorder the array
    testnotes[0] = testnotes[1]; testnotes[1] = testnotes[2]; testnotes[2] = temp+12;
  }
  if (!flag) {
    printf("Notes Do not form a triad\n");
  }
}

void swap(int* v1, int* v2) {
  int temp = *v2;
  *v2 = *v1;
  *v1 = temp;
}
