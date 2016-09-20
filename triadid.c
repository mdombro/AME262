#include <stdio.h>
#include <math.h>
#include <string.h>

void swap(int* v1, int* v2);

int main() {
  char notes[3][3] = {};
  char strnote[3][7] = {"first", "second", "third"};
  char strclasses[][6] = {"C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B"};
  int classes[3];

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
    printf("%s\n", notes[o]);
    for (int i = 0; i < 12; i++) {
      if (notes[o][1] == '\0' && strclasses[i][2] == '/')
        continue;
      if (strstr(strclasses[i], notes[o]) == NULL)
        class = 0;
      else {
        class = i; break;
      }
    }
    classes[o] = class;
  }

  // classify triad
  for (int i = 0; i < 2; i++) {
    for (int o = 0; o < 2-i; o++) {
      if (classes[o] > classes[o+1]) {
        swap(&classes[o], &classes[o+1]);
      }
    }
  }
  printf("%d  %d  %d\n", classes[0],classes[1],classes[2]);
  switch (classes[2]-classes[0]) {
    case 7: {
      if (classes[1]-classes[0] == 3)
        printf("%s - %s - %s forms a minor triad\n", strclasses[0], strclasses[1], strclasses[2]);
      if (classes[1] - classes[0] == 4)
        printf("%s - %s - %s forms a major triad\n", strclasses[0], strclasses[1], strclasses[2]);
      break;
    }
    case 6: {
      if (classes[1]-classes[0] == 3)
        printf("%s - %s - %s forms a diminished triad\n", strclasses[0], strclasses[1], strclasses[2]);
      break;
    }
    case 8: {
      if (classes[1]-classes[0] == 4)
        printf("%s - %s - %s forms a augmented triad\n", strclasses[0], strclasses[1], strclasses[2]);
      break;
    }
    default:
      printf("Notes do not form a triad\n");
      break;
  }
}

void swap(int* v1, int* v2) {
  int temp = *v2;
  *v2 = *v1;
  *v1 = temp;
}
