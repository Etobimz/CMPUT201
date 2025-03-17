#include <stdio.h>


int main () {

#define  N 4
int a[N];

int sum = 0;

for (int i=0; i<N; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
//return sum;

}

printf("sum is: %d\n", sum);

return 0;

}