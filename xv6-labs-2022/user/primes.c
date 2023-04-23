#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stdarg.h>
const char ERRORMSG[] = "fork() error\n";
int main() {
  int pid;
  int i = -1;
  int p[2][2];
  for(i = 0; i < 12; ++i) {
    pipe(p[1]);
    pid = fork();
    if(pid > 0) {
      break;
    } else if(pid == 0) {
      p[0][0] = p[1][0];
      close(p[1][1]);
    } else {
      write(2, ERRORMSG, strlen(ERRORMSG));
    }
  }

  if(i > 0) {
    int num;
    read(p[0][0],&num,sizeof(int));
    printf("prime %d\n", num);
    int num2;
    while(read(p[0][0],&num2,sizeof(int))) {
      if(num2 % num) {
        write(p[1][1],&num2,sizeof(int));
      }
    }
    close(p[0][0]);
    if(i < 12) {
      close(p[1][0]);
      close(p[1][1]);
      wait(0);
    }
  } else {
    close(p[1][0]);
    int i = 2;
    for(; i <= 35; ++i) {
      write(p[1][1], &i, sizeof(int));
    }
    close(p[1][1]);
    wait(0);
  }

  exit(0);
}
