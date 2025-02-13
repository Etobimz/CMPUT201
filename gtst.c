#include <stdio.h>

int main(){

int x, y;

int result = scanf("%d %d", &x,&y);

if (result == 2) {
	printf("right result\n");

}

else if (result == 1) { 
        printf("1 more var needed\n");

}

else if (result == '\n' ) {
        printf("EOF\n");
}
return 0;
}
