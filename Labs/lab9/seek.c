#include <stdio.h>

int main() {
  char buff[256];
  scanf("%s", buff);
  FILE *fp = fopen(buff, "r");
  int x;
  fscanf(fp, "%d", &x);
  fseek(fp, x, SEEK_CUR);
  fscanf(fp, "%d", &x);
  printf("%d\n", x);
  fclose(fp);
}
