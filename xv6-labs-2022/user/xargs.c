#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char **argv) {
  char *cmd = argv[1];
  char arg[512] = {0};
  int index = 0;
  char ch;
  while(read(0,&ch,sizeof(char))) {
    if(ch != '\n') {
      arg[index] = ch;
      ++index;
    } else {
      arg[index] = 0;
      index = 0;
      if(fork() == 0) {
        char *cargv[MAXARG];
        for(int i = 1; i < argc; ++i) {
          cargv[i-1] = malloc(strlen(argv[i]) + 1);
          memcpy(cargv[i-1],argv[i], strlen(argv[i]) + 1);
        }
        cargv[argc - 1] = malloc(strlen(arg) + 1);
        memcpy(cargv[argc - 1], arg,strlen(arg) + 1);
        cargv[argc] = 0;
        exec(cmd, cargv);
      } else {
        wait(0);
      }
    }
  }
  exit(0);
}
