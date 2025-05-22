#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NPROC 10

int priorities[NPROC] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main(void) {
    int k;
    uint64 total_waiting_time = 0;

    printf("Starting deterministic priority test with %d processes...\n", NPROC);

    for (k = 0; k < NPROC; k++) {
        int pid = fork();
        if (pid < 0) {
            printf("Fork failed\n");
            exit(1);
        } else if (pid == 0) {
            // Child: set priority and do work
            setpriority(priorities[k]);

            // Simulate CPU work
            char buf1[512], buf2[512];
            for (int i = 0; i < 500000; i++) {
                memmove(buf2, buf1, 512);
                memmove(buf1, buf2, 512);
            }
            exit(0);
        } else {
            printf("[pid=%d] created with priority %d\n", pid, priorities[k]);
        }
    }

    printf("\nWaiting for all children to finish...\n");

    for (k = 0; k < NPROC; k++) {
        int status;
        int pid = wait(&status);
        uint64 curr_wait = (uint64)status;
        total_waiting_time += curr_wait;
        printf("[pid=%d] terminated | Wait time: %lu\n", pid, curr_wait);
    }

    printf("\nTotal wait time: %lu\n", total_waiting_time);
    printf("Average wait time: %lu\n", total_waiting_time / NPROC);

    exit(0);
}
