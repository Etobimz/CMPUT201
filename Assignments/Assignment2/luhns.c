#include <stdio.h>

int main() {
    long long sum = 0;
    int count = 0;
    int digit;
    int check_digit = -1;
    char ch;
    long long temp = 0;

    // First: Count digits and build number
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (ch >= '0' && ch <= '9') {
            digit = ch - '0';
            temp = temp * 10 + digit;
            count++;
            check_digit = digit;
        }
    }

    if (count < 2) {
        printf("Invalid\n");
        return 0;
    }

    // Process right-to-left, adjusting doubling based on count
    temp /= 10; // Remove check digit
    int pos_from_right = 1;
    while (temp > 0) {
        digit = temp % 10;
        temp /= 10;
        if (pos_from_right % 2 == 1) { // Correct doubling (second from right)
            digit *= 2;
            if (digit >= 10) {
                digit -= 9;
            }
        }
        sum += digit;
        pos_from_right++;
    }

    if ((sum + check_digit) % 10 == 0) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}