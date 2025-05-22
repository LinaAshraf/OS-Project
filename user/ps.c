#include "user.h"

int main()
{
    struct pstat stats[64];
    int count = getptable(stats, sizeof(stats)/sizeof(stats[0]));

    if(count < 0) {
        fprintf(2, "Error getting process table\n");  // Changed to fprintf
        exit(0);
    }

    fprintf(1, "PID\tPPID\tSTATE\t\tNAME\tSIZE\n");  // Changed to fprintf
    for(int i = 0; i < count; i++) {
      fprintf(1, "%d\t%d\t%s\t%s\t%lu\n",  // Changed %d to %lu for uint64
        stats[i].pid, stats[i].ppid,
        stats[i].state, stats[i].name,
        stats[i].size);  // Now matches format specifier
    }
    exit(0);
}
