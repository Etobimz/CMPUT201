#include <stdio.h>

#define INT_MIN_VALUE (-2147483648)
#define INT_MAX_VALUE (2147483647)

int main() {
    char filename[256];
    FILE *file;
    int current, min, found, count;

    // Read the filepath from standard input
    if (scanf("%255s", filename) != 1) {
        printf("Invalid filename input\n");
        return 1;
    }

    // Open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    int last_printed = INT_MIN_VALUE;

    while (1) {
        // Reset file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);
        min = INT_MAX_VALUE;
        found = 0;
        count = 0;

        while (fscanf(file, "%d", &current) == 1) {
            // Only consider numbers strictly greater than the last printed value
            if (current > last_printed && current < min) {
                min = current;
                found = 1;
                count = 1;
            } else if (current == min) {
                count++;
            }
        }

        // If no new number is found, we're done
        if (!found) break;

        // Print the found minimum number as many times as it occurs
        for (int i = 0; i < count; i++) {
            printf("%d ", min);
        }

        last_printed = min;
    }

    printf("\n");
    fclose(file);
    return 0;
}
