#include <stdio.h>

int main() {
  char arr[6];
  while (scanf("%5s", arr) == 1) {
    printf("String read in: \"%s\"\n", arr);
  }
}
