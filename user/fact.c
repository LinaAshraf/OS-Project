#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

// Function to calculate factorial recursively
unsigned int factorial(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(2, "Usage: fact <non-negative integer>\n");
        exit(0);
    }

    // Check if the argument is a valid non-negative integer
    char *p = argv[1];
    while (*p != '\0') {
        if (*p < '0' || *p > '9') {
            fprintf(2, "fact: Error - argument must be a non-negative integer\n");
            exit(0);
        }
        p++;
    }

    int n = atoi(argv[1]);

    // Calculate and print factorial
    unsigned int result = factorial(n);
    fprintf(1, "%d! = %d\n", n, result);

    exit(0);
}
