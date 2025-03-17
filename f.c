#include <stdio.h>

int main() { 
    char name[20];
    char fullname[90];

printf("Input name: ");
scanf("%s", name);

while (getchar() !=  '\n');

printf("Input full name: ");
fgets(fullname, sizeof(fullname), stdin);

printf("Name is: %s\n", name);
printf("Fullname is: %s\n", fullname);

return 0;



}


#define Q 15
