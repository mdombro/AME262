#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int num = atoi(argv[1]);
  for (int i = 0; i < num; i++) {
    printf("I love audio engineering\n");
  }
  printf("argc = %d\n", argc);
}
