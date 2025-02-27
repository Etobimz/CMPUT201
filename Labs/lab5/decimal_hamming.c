# include <stdio.h>

int main() {

    unsigned int a , b;
    scanf("%u %u", &a, &b);
    int count  = 0;


    
    

    while ( a != 0 )

    {

        if (a%10 != b % 10) {
            ++count; 

            };

        a  = a/10; 
        b  = b/10;
            
    }



    printf("%d\n", count);


    
return 0;

}

