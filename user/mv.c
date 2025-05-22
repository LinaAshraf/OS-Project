#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
    struct stat st;

    if(argc != 3) {
        fprintf(2, "Usage: mv <source> <destination>\n");
        exit(1);
    }

    // Check if source exists
    if(stat(argv[1], &st) < 0) {
        fprintf(2, "mv: cannot stat '%s'\n", argv[1]);
        exit(1);
    }

    // Check if source is a directory (xv6 doesn't support directory moving)
    if(st.type == T_DIR) {
        fprintf(2, "mv: cannot move directories\n");
        exit(1);
    }

    // Try to link (rename) the file
    if(link(argv[1], argv[2]) < 0) {
        fprintf(2, "mv: failed to move '%s' to '%s'\n", argv[1], argv[2]);
        exit(1);
    }

    // Unlink the original file
    if(unlink(argv[1]) < 0) {
        fprintf(2, "mv: failed to remove original '%s'\n", argv[1]);
        // Attempt to clean up the new link if unlink failed
        unlink(argv[2]);
        exit(1);
    }

    exit(0);
}
