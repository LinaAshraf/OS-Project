#include "user.h"

int main() {
    printf("My PID: %d\n", getpid());
    printf("Parent's PID: %d\n", getppid());
    return 0;
}
