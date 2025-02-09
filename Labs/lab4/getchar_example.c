#include <stdio.h>

int main() {
  /*
    The function getchar takes no parameters and will produce for us
    the immediate next character that is read from the stdin input stream
    (Technically, getchar returns an int, more on that later)
  */
  char c1 = getchar();
  char c2 = getchar();
  printf("The two characters are '%c' (ascii %d) and '%c' (ascii %d)\n", c1, c1, c2, c2);
}
