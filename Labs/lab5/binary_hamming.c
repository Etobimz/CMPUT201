# include <stdio.h>

int main() {

    unsigned int a , b;
    scanf("%u %u", &a, &b);
    int count  = 0;


    
    

    while ( a != 0 )

    {

        if (a%2 != b%2) {
            ++count; 

            };

        a  = a/2; 
        b  = b/2;
            
    }



    printf("%d\n", count);


    
return 0;

}

