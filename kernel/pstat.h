#include "types.h"
struct pstat {
  int pid;        // Process ID
  int ppid;       // Parent PID
  char state[16]; // Process state
  char name[16];  // Process name
  uint64 size;    // Memory size
};
