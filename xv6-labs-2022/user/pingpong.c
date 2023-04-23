#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stdarg.h>
const char MSG[] = "TEST MSG!\n";
const char ERRORMSG[] = "fork() error!\n";
int main() {
  int pid;
  char buf[20];
  int len = strlen(MSG);
  int p[2];
  pipe(p);
  pid = fork();
  if(pid > 0) {
    int pid1 = getpid(); 
    write(p[1], MSG, len);
    read(p[0],buf, len);
    printf("%d: received pong\n", pid1);
    close(p[0]);
    close(p[1]);
  } else if(pid == 0) {
    read(p[0],buf,len);
    int pid2 = getpid();
    printf("%d: received ping\n", pid2);
    write(p[1],MSG,len);
    close(p[0]);
    close(p[1]);
  } else {
    write(2, ERRORMSG, strlen(ERRORMSG));
  }
  exit(0);
}
