#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure to represent a pixel with R, G, B values
typedef struct {
    int r, g, b;
} Pixel;

// Structure to represent the image
typedef struct {
    int width, height;
    Pixel **pixels; // 2D array: pixels[height][width]
} Image;

// Function to read the PPM image from stdin
Image *read_image(int *error) {
    char format[3];
    int width, height, maxval;

    if (scanf("%2s", format) != 1 || strcmp(format, "P3") != 0) {
        fprintf(stderr, "Invalid PPM format: expected P3\n");
        *error = 1;
        return NULL;
    }
    if (scanf("%d %d", &width, &height) != 2 || width <= 0 || height <= 0) {
        fprintf(stderr, "Invalid dimensions: width and height must be positive\n");
        *error = 1;
        return NULL;
    }
    if (scanf("%d", &maxval) != 1 || maxval != 255) {
        fprintf(stderr, "Invalid max color value: expected 255\n");
        *error = 1;
        return NULL;
    }

    Image *image = malloc(sizeof(Image));
    if (image == NULL) {
        fprintf(stderr, "Memory allocation failed for image\n");
        *error = 1;
        return NULL;
    }
    image->width = width;
    image->height = height;

    image->pixels = malloc(height * sizeof(Pixel *));
    if (image->pixels == NULL) {
        fprintf(stderr, "Memory allocation failed for pixel rows\n");
        free(image);
        *error = 1;
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        image->pixels[i] = malloc(width * sizeof(Pixel));
        if (image->pixels[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for pixel row %d\n", i);
            for (int j = 0; j < i; j++) {
                free(image->pixels[j]);
            }
            free(image->pixels);
            free(image);
            *error = 1;
            return NULL;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r, g, b;
            if (scanf("%d %d %d", &r, &g, &b) != 3 ||
                r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                fprintf(stderr, "Invalid pixel data at row %d, column %d\n", i, j);
                for (int k = 0; k < height; k++) {
                    free(image->pixels[k]);
                }
                free(image->pixels);
                free(image);
                *error = 1;
                return NULL;
            }
            image->pixels[i][j].r = r;
            image->pixels[i][j].g = g;
            image->pixels[i][j].b = b;
        }
    }
    *error = 0;
    return image;
}

// Function to free the image memory
void free_image(Image *image) {
    if (image == NULL) return;
    for (int i = 0; i < image->height; i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
    free(image);
}

// Function to apply the sepia filter to the image
void apply_sepia(Image *image) {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            int r = image->pixels[i][j].r;
            int g = image->pixels[i][j].g;
            int b = image->pixels[i][j].b;
            int newR = (int)(r * 0.393 + g * 0.769 + b * 0.189);
            int newG = (int)(r * 0.349 + g * 0.686 + b * 0.168);
            int newB = (int)(r * 0.272 + g * 0.534 + b * 0.131);
            image->pixels[i][j].r = (newR > 255 ? 255 : newR);
            image->pixels[i][j].g = (newG > 255 ? 255 : newG);
            image->pixels[i][j].b = (newB > 255 ? 255 : newB);
        }
    }
}

// Function to flip the image horizontally
void flip_image(Image *image) {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width / 2; j++) {
            Pixel temp = image->pixels[i][j];
            image->pixels[i][j] = image->pixels[i][image->width - 1 - j];
            image->pixels[i][image->width - 1 - j] = temp;
        }
    }
}

// Function to print the image in P3 format (one row per line, each pixel with trailing space)
void print_image(const Image *image) {
    printf("P3\n");
    printf("%d %d\n", image->width, image->height);
    printf("255\n");

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%d %d %d ", image->pixels[i][j].r,
                                 image->pixels[i][j].g,
                                 image->pixels[i][j].b);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int error = 0;
    Image *image = read_image(&error);
    if (error) {
        return 1;
    }

    bool do_flip = false;
    bool do_sepia = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            do_flip = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            do_sepia = true;
        } else {
            fprintf(stderr, "Invalid argument: %s. Use -f to flip, -s for sepia.\n", argv[i]);
            free_image(image);
            return 1;
        }
    }

    if (do_flip) {
        flip_image(image);
    }
    if (do_sepia) {
        apply_sepia(image);
    }

    print_image(image);
    free_image(image);
    return 0;
}

