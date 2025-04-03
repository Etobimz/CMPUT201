#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REDACT 10
#define MAX_WORD_LEN 256

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    
    // Read up to 10 strings from standard input.
    char redacts[MAX_REDACT][MAX_WORD_LEN];
    int redactCount = 0;
    while (redactCount < MAX_REDACT && scanf("%255s", redacts[redactCount]) == 1) {
        redactCount++;
    }
    
    // Open the file in read-write mode.
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }
    
    // Determine file size.
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate a buffer to hold the file's contents.
    char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }
    
    // Read the file into the buffer.
    size_t readSize = fread(buffer, 1, filesize, file);
    buffer[readSize] = '\0'; // Null-terminate the content.
    
    // For each redaction word, replace all occurrences in the buffer.
    for (int i = 0; i < redactCount; i++) {
        char *word = redacts[i];
        size_t wordLen = strlen(word);
        char *pos = buffer;
        // Loop until no further occurrence is found.
        while ((pos = strstr(pos, word)) != NULL) {
            // Replace each character in the found word with 'X'.
            for (size_t j = 0; j < wordLen; j++) {
                pos[j] = 'X';
            }
            pos += wordLen; // Move pointer past the redacted word.
        }
    }
    
    // Write the modified buffer back to the file.
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, readSize, file);
    
    // Free resources and close file.
    free(buffer);
    fclose(file);
    
    return 0;
}
