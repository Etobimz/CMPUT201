#include <stdio.h>

int num_length(int num)  // counting the length of the input number
 {
    int count = 0;
    if (num == 0) return 1;  // Special case for zero
    if (num < 0) num = -num; // Convert negative to positive

    while (num > 0)
    {
        
        num = num / 10; 
        ++count;

    }

    return count;

}

int factor_num(int num_length) { // Function to know how many spaces to the left to place the new number
        int factor = 1;
    for (int i = 1; i< num_length; ++i) {
        factor = factor * 10;

    

    }
    return factor;
}

int main() {
    int input_number;
    if (scanf("%d", &input_number) != 1) return 1; // Handle input failure
    printf("%d\n", input_number);
    int number_length = num_length(input_number);
    int Factor = factor_num(number_length);
    int count  = 0;
    int flipped_num = input_number;

    

    while (count < number_length-1)
    {
        
        int Last_digit = flipped_num % 10;
        flipped_num = flipped_num / 10;
        flipped_num = Last_digit * Factor + flipped_num;
        printf("%d\n", flipped_num);
        ++count;

    

    }
    

    return 0;
}