#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 10
#define MAX_GUESSES 6
int same_spot_bull(const char *guess, const char *codeword, int *bull_flags) {
  int count =0;

  // iterate over both strings
  for (int i = 0; i < MAX_LENGTH && codeword[i] != '\0' && guess[i] != '\0'; ++i) {

    if (codeword[i] == guess[i] ) {

      count++;
      bull_flags[i] = 1; // mark the position as bull
    
    }
   
  }

   return count;

}


int char_diffrent_spot(char c, const char *str ) {
    int count =0;

    // iterate over both strings
    for (int i = 0; str[i] != '\0'; ++i) {
      if (str[i] == c ) {
        count ++;

      }



    }

  return count;

  }


int count_cows(const char *guess, const char *codeword, int *bull_flags) {
    int cow_count = 0;
    int codeword_letter_count[256] = {0};  // Counts occurrences of each letter in codeword (ignoring Bulls)
    int guess_letter_count[256] = {0};     // Tracks how many times each letter is counted as a Cow

    // Count occurrences of each letter in codeword (ignoring bulls)
    for (int i = 0; codeword[i] != '\0'; ++i) {
        if (!bull_flags[i]) {  // Only count letters that are NOT Bulls
            unsigned char index = (unsigned char)codeword[i];  // Safe indexing
            codeword_letter_count[index]++;
        }
    }

    // Count Cows (right letter, wrong position)
    for (int i = 0; guess[i] != '\0'; ++i) {
        if (!bull_flags[i]) {  // Only check for Cows if it's not already a Bull
            unsigned char index = (unsigned char)guess[i];  // Safe indexing

            // Only count a cow if there's still an available occurrence in codeword
            if (codeword_letter_count[index] > 0 && guess_letter_count[index] < codeword_letter_count[index]) {
                cow_count++;
                guess_letter_count[index]++;  // Track that this letter has been counted as a cow
            }
        }
    }

    return cow_count;
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <codeword>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[1]) > MAX_LENGTH) {
        fprintf(stderr, "Error: codeword can be at most %d characters\n", MAX_LENGTH);
        return 1;
    }

    const char * const codeword = argv[1];
    int codeword_length = strlen(codeword);
    char guess[MAX_LENGTH + 1];
    int guess_count = 0;

    // Game loop for 6 guesses
    while (guess_count < MAX_GUESSES) {
        printf("\nEnter guess (%d characters): ", codeword_length);
        if (scanf("%10s", guess) == EOF) {
            break;  // Exit early on EOF
        }

        // Ensure guess is the same length as the codeword
        if (strlen(guess) != codeword_length) {
            printf("Invalid guess length. Must be %d characters.\n", codeword_length);
            continue;
        }

        int bull_flags[MAX_LENGTH] = {0};  // Track Bulls to prevent double counting
        int bulls = same_spot_bull(guess, codeword, bull_flags);
        int cows = count_cows(guess, codeword, bull_flags);

        printf("Bulls: %d, Cows: %d\n", bulls, cows);

        // Check if all bulls are found
        if (bulls == codeword_length) {
            return 0;  // Exit 
        }

        guess_count++;
    }

    printf("\nGame Over. The codeword was: %s\n", codeword);
    return 0;
}

  





//1
// bull right letter right position
// cow right letter wrong position

//2
//if already awarded to bull, it shouldnt be awarded to cow

//3
// only the amout of that particular letters can be given
// codewordd - hello
// guess - llxxl
// {just 0 bulls and 2 cows since thyare are only 2 available lls in hello}