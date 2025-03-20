#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readString() {
    int capacity = 16; // Initial buffer size
    char *buffer = malloc(capacity);
    if (!buffer) return NULL; // Check memory allocation failure
    int len = 0, ch; // ch is used to store the current character being read.

    // Skip leading whitespaces
    while ((ch = getchar()) != EOF && (ch == '\t' || ch == ' ' || ch == '\n'));

    if (ch == EOF) { // If EOF is reached before reading anything, free memory
        free(buffer);
        return NULL;
    }

    int quote = (ch == '"'); // A boolean to check if it's a quoted string
    if (!quote) buffer[len++] = ch; // Store first character if not quoted

    while ((ch = getchar()) != EOF) {
        if (quote) {
            if (ch == '"') break; // Stop at closing quote
        } else {
            if (ch == ' ' || ch == '\t' || ch == '\n') break; // Stop at whitespace for unquoted strings
        }

        // Expand the buffer if needed
        if (len + 1 >= capacity) {
            capacity *= 2;
            char *newBuffer = realloc(buffer, capacity);
            if (!newBuffer) {
                free(buffer); // In case realloc fails, free the old buffer and return NULL
                return NULL;
            }
            buffer = newBuffer;
        }

        buffer[len++] = ch;
    }

    buffer[len] = '\0'; // Null-terminate the string
    return buffer; // Return the dynamically allocated string
}

int main() {
    char *p;
    while ((p = readString())) {
        printf("%s\n", p);
        free(p);
    }
}
