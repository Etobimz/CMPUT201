#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char operator[4]; // "add", "sub", "mul", "div"
    int operand;
} Operation;

// Apply a single operation to a value, returning an error indicator
int applyOperation(int current, const char *operator, int operand, int *error) {
    long long result = current;
    if (strcmp(operator, "add") == 0) {
        result += operand;
    } else if (strcmp(operator, "sub") == 0) {
        result -= operand;
    } else if (strcmp(operator, "mul") == 0) {
        result *= operand;
    } else if (strcmp(operator, "div") == 0) {
        if (operand == 0) {
            fprintf(stderr, "Division by zero\n");
            *error = 1;
            return 0; // Dummy return value; error flag is set
        }
        result /= operand;
    }
    if (result < -2147483648LL || result > 2147483647LL) {
        fprintf(stderr, "Operation result out of int range\n");
        *error = 1;
        return 0; // Dummy return value; error flag is set
    }
    *error = 0;
    return (int)result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <initial_value>\n", argv[0]);
        return 1;
    }

    int current;
    if (sscanf(argv[1], "%d", &current) != 1) { //
        fprintf(stderr, "Invalid initial value\n");
        return 1;
    }

    int capacity = 4;
    int num_ops = 0;
    Operation *ops = malloc(capacity * sizeof(Operation));
    if (ops == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char token[10];
    int operand;
    int error = 0;
    int exit_code = 0;

    while (scanf("%s", token) != EOF) {
        if (strcmp(token, "n") == 0) {
            int next = current;
            for (int i = 0; i < num_ops; i++) {
                next = applyOperation(next, ops[i].operator, ops[i].operand, &error);
                if (error) {
                    exit_code = 1;
                    goto cleanup;
                }
            }
            printf("%d\n", next);
            current = next;
        } else {
            if (scanf("%d", &operand) != 1) {
                fprintf(stderr, "Invalid operand\n");
                exit_code = 1;
                goto cleanup;
            }
            if (strcmp(token, "add") != 0 && strcmp(token, "sub") != 0 &&
                strcmp(token, "mul") != 0 && strcmp(token, "div") != 0) {
                continue;
            }
            if (num_ops == capacity) {
                capacity *= 2;
                Operation *new_ops = realloc(ops, capacity * sizeof(Operation));
                if (new_ops == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit_code = 1;
                    goto cleanup;
                }
                ops = new_ops;
            }
            strcpy(ops[num_ops].operator, token);
            ops[num_ops].operand = operand;
            num_ops++;
        }
    }

cleanup:
    free(ops);
    return exit_code;
}