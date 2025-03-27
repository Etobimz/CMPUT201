#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(2 * sizeof(int));
    *p = 14;
    printf("%d", *p);

    free(p);
    p = NULL;
return 0;

}