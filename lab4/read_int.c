#include <stdio.h>

int readint() {
  /*
   * This function takes no parameters, reads in an integer
   * from the stdin stream (using the getchar function),
   * and returns that integer. This should skip over any leading
   * whitespace, and then stop reading the integer the first
   * time a non-digit character is read.
   */

	 char  ch;
	int num = 0;
	while (( ch =  getchar()) == ' ' || ch == '\t'  || ch == '\n' ) { }; //{} do nothing


	while  ( ch  >= '0' && ch <= '9' ) { 
	num = num * 10 + (ch -  '0');
	ch = getchar();

}
	return num;
}

int main() {
  // This program reads one integer from the standard input stream
  // and prints out that integer multiplied by 3!
  int x = readint();
  printf("%d\n", x*3);
}
