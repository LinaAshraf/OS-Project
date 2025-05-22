#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "Usage: touch <filename>\n");
    exit(1);
  }

  // First try to open the file in read-only mode to check existence
  int check_fd = open(argv[1], O_RDONLY);
  if (check_fd >= 0) {
    // File already exists
    close(check_fd);
    fprintf(2, "touch: cannot create '%s': File already exists\n", argv[1]);
    exit(1);
  }

  // File doesn't exist, create it
  int fd = open(argv[1], O_CREATE | O_WRONLY);
  if (fd < 0) {
    fprintf(2, "touch: failed to create '%s'\n", argv[1]);
    exit(1);
  }

  close(fd);
  exit(0);
}
