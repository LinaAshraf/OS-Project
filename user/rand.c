#include "user.h"

int main() {
    fprintf(1, "Random numbers:\n");
    for(int i = 0; i < 10; i++) {
        fprintf(1, "%d\n", random());
    }
    exit(0);
}
