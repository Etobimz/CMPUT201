#include <stdio.h>

int numeral_conversion(char c) {
    if (c == 'I'){
        return 1;
    } if (c == 'V'){
        return 5;
    } if (c == 'X'){
        return 10;
    } if (c == 'L'){
        return 50;
    } if (c == 'C'){
        return 100;
    } if (c == 'D'){
        return 500;
    } if (c == 'M'){
        return 1000;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int converted_result;
    int current;
    int previous;
    int i;
    char roman_numeral;

    converted_result = 0;
    previous = 0;

    if (argc == 2) { 
        for (i = 0; argv[1][i] != '\0'; i++) {
            roman_numeral = argv[1][i];
            current = numeral_conversion(roman_numeral);
            if (previous < current) {
                converted_result += current - 2 * previous;
            } else {
                converted_result += current;
            }
            previous = current;
        }
    } else {
        while ((roman_numeral = getchar()) != EOF && roman_numeral != '\n') {
            current = numeral_conversion(roman_numeral);
            if (previous < current) {
                converted_result += current - 2 * previous;
            } else {
                converted_result += current;
            }
            previous = current;
        }
    }
    printf("%d\n", converted_result);
}