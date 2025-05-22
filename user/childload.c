#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: childload <priority>\n");
        exit(1);
    }

    int priority = atoi(argv[1]);
    setpriority(priority);

    char buf1[1024], buf2[1024];
    for (int i = 0; i < 1000000; i++) {
        memmove(buf2, buf1, 1024);
        memmove(buf1, buf2, 1024);
    }

    exit(0);
}
