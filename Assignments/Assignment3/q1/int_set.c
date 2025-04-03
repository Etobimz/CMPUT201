#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int length, int val) {
    int left = 0, right = length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == val) return mid;
        if (arr[mid] < val) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

void add(int **arr, int *length, int *capacity, int val) {
    if (*length == 0 || val > (*arr)[*length - 1]) {
        if (*length == *capacity) {
            int new_capacity = *capacity * 2;
            int *newArr = (int *)malloc(new_capacity * sizeof(int));
            if (newArr == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            for (int i = 0; i < *length; i++) {
                newArr[i] = (*arr)[i];
            }
            free(*arr);
            *arr = newArr;
            *capacity = new_capacity;
        }
        (*arr)[*length] = val;
        (*length)++;
        return;
    }

    int pos = binarySearch(*arr, *length, val);
    if (pos < *length && (*arr)[pos] == val) return;

    if (*length == *capacity) {
        int new_capacity = *capacity * 2;
        int *newArr = (int *)malloc(new_capacity * sizeof(int));
        if (newArr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        for (int i = 0; i < *length; i++) {
            newArr[i] = (*arr)[i];
        }
        free(*arr);
        *arr = newArr;
        *capacity = new_capacity;
    }

    for (int i = *length; i > pos; i--) {
        (*arr)[i] = (*arr)[i - 1];
    }
    (*arr)[pos] = val;
    (*length)++;
}

void removeElement(int *arr, int *length, int val) {
    int pos = binarySearch(arr, *length, val);
    if (pos >= *length || arr[pos] != val) return;

    for (int i = pos; i < *length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*length)--;
}

void printSet(int *arr, int length) {
    if (length == 0) {
        return;
    }
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) printf(" ");
    }
    printf("\n");
}

void printUnion(int *arrX, int lengthX, int *arrY, int lengthY) {
    int i = 0, j = 0;
    int first = 1;
    int lastVal = 0;
    while (i < lengthX || j < lengthY) {
        int val;
        if (i < lengthX && (j >= lengthY || arrX[i] <= arrY[j])) {
            val = arrX[i++];
        } else {
            val = arrY[j++];
        }
        if (first || val != lastVal) {
            if (!first) printf(" ");
            printf("%d", val);
            lastVal = val;
            first = 0;
        }
    }
    printf("\n");
}

void printIntersection(int *arrX, int lengthX, int *arrY, int lengthY) {
    int i = 0, j = 0;
    int first = 1;
    while (i < lengthX && j < lengthY) {
        if (arrX[i] == arrY[j]) {
            if (!first) printf(" ");
            printf("%d", arrX[i]);
            i++;
            j++;
            first = 0;
        } else if (arrX[i] < arrY[j]) {
            i++;
        } else {
            j++;
        }
    }
    printf("\n");
}

int main() {
    int capacityX = 4;
    int lengthX = 0;
    int *arrX = (int *)malloc(capacityX * sizeof(int));
    if (arrX == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int capacityY = 4;
    int lengthY = 0;
    int *arrY = (int *)malloc(capacityY * sizeof(int));
    if (arrY == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(arrX);
        exit(1);
    }

    char command;
    char target[2];
    long long value;

    while (1) {
        int c;
        do {
            c = getchar();
            if (c == EOF) {
                command = 'q';
                break;
            }
        } while (c == ' ' || c == '\n' || c == '\t');
        command = (char)c;

        if (command == 'q') break;

        if (command == 'a' || command == 'r' || command == 'p') {
            do {
                c = getchar();
                if (c == EOF) {
                    command = 'q';
                    break;
                }
            } while (c == ' ' || c == '\n' || c == '\t');
            if (command == 'q') break;
            target[0] = (char)c;
            target[1] = '\0';

            if (target[0] != 'x' && target[0] != 'y') {
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }

            if (command == 'a' || command == 'r') {
                do {
                    c = getchar();
                    if (c == EOF) {
                        command = 'q';
                        break;
                    }
                } while (c == ' ' || c == '\n' || c == '\t');
                if (command == 'q') break;

                ungetc(c, stdin);
                if (scanf("%lld", &value) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    continue;
                }

                if (value < -2147483648LL || value > 2147483647LL) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    continue;
                }

                if (command == 'a') {
                    if (target[0] == 'x') {
                        add(&arrX, &lengthX, &capacityX, (int)value);
                    } else if (target[0] == 'y') {
                        add(&arrY, &lengthY, &capacityY, (int)value);
                    }
                } else if (command == 'r') {
                    if (target[0] == 'x') {
                        removeElement(arrX, &lengthX, (int)value);
                    } else if (target[0] == 'y') {
                        removeElement(arrY, &lengthY, (int)value);
                    }
                }
            } else if (command == 'p') {
                if (target[0] == 'x') {
                    printSet(arrX, lengthX);
                } else if (target[0] == 'y') {
                    printSet(arrY, lengthY);
                }
            }
        } else if (command == 'u') {
            printUnion(arrX, lengthX, arrY, lengthY);
        } else if (command == 'i') {
            printIntersection(arrX, lengthX, arrY, lengthY);
        } else {
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        while ((c = getchar()) != '\n' && c != EOF);
        if (c == EOF && command != 'q') break;
    }

    free(arrX);
    free(arrY);
    return 0;
}