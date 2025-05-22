#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: cp <source> <destination>\n");
    exit(1);
  }

  char *src = argv[1];
  char *dst = argv[2];

  int src_fd = open(src, O_RDONLY);
  if (src_fd < 0) {
    printf("cp: cannot open source file %s\n", src);
    exit(1);
  }

  int dst_fd = open(dst, O_CREATE | O_WRONLY);
  if (dst_fd < 0) {
    printf("cp: cannot create destination file %s\n", dst);
    close(src_fd);
    exit(1);
  }

  char buf[512];
  int n;
  while ((n = read(src_fd, buf, sizeof(buf))) > 0) {
    if (write(dst_fd, buf, n) != n) {
      printf("cp: write error\n");
      close(src_fd);
      close(dst_fd);
      exit(1);
    }
  }

  if (n < 0) {
    printf("cp: read error\n");
  }

  close(src_fd);
  close(dst_fd);
  exit(0);
}
