#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *zipStrings(const char *s1, const char *s2) {
  // Takes two string parameters s1 and s2 of the same length
  // and returns a new heap allocated string that is the result of
  // "zipping" the two strings together.
  // e.g. zipStrings("abc", "xyz") -> "axbycz"
  

  char *s = malloc(strlen(s1)+strlen(s2) + 1);

  char *new_ar = s;
  

while ( (*s1 !=  '\0'))
{
  *s = *s1;
  s++;
  *s = *s2;
  s++;
  s1++;
  s2++;

}
return new_ar;



}


int main() {
  char s1[256];
  char s2[256];
  scanf("%s", s1);
  scanf("%s", s2);
  char *p = zipStrings(s1, s2);
  printf("%s\n", p);
  free(p);
}
