#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"

int
main(void)
{
  int count = countsyscall();
  printf("Total system calls: %d\n", count);
  exit(0);
}
