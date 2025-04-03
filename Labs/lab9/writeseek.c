#include <stdio.h>

int main() {
  FILE *f = fopen("writeseek.txt", "w");
  fprintf(f, "wow what is going on!\n");
  fseek(f, -7, SEEK_CUR);
  fprintf(f, "huh?!");
}
