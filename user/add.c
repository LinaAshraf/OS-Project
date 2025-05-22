#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main (int argc,char  *argv[]){

  if(argc != 3) {
    printf("Usage error you can only use two numbers\n");
    exit(0);
  }

  if(strcmp(argv[1], "?") == 0) {
    printf("This function adds two numbers and prints the result\n");
    exit(0);
  }

  int n1=atoi (argv[1]);
  int n2=atoi(argv[2]);

 int n3=n1+n2;
 printf("%d\n",n3);

  exit(0);

}
