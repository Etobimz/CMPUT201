#include <stdio.h>
#include <stdlib.h>

// Function to count adjacent bombs for a given (x, y) coordinate
int count_adjacent_bombs(char **grid, int x, int y, int width, int height) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int new_x = x + dx;
            int new_y = y + dy;
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height && grid[new_y][new_x] == 'X') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int width, height;
    if (scanf("%d %d", &width, &height) != 2) {
        return 1;
    }

    // Allocate grid
    char **grid = (char **)malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        grid[i] = (char *)malloc(width * sizeof(char));
    }

    // Read grid
    int row = 0, col = 0;
    char c;
    while (row < height && scanf("%c", &c) == 1) {
        if (c == 'X' || c == 'O') {
            grid[row][col] = c;
            col++;
            if (col == width) {
                col = 0;
                row++;
            }
        }
    }

    // Print the grid
    printf("Grid:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    // Process coordinates
    int x, y;
    while (scanf("%d %d", &x, &y) == 2) {
        if (grid[y][x] == 'X') {
            printf("BOMB!\n");
        } else {
            int bomb_count = count_adjacent_bombs(grid, x, y, width, height);
            printf("%d\n", bomb_count);
        }
    }

    // Free memory
    for (int i = 0; i < height; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}