
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const char ERRORMSG[] = "Please input an interger!\n";
int main(int argc, char *argv[]) {
  if(argc == 1) {
    write(2,ERRORMSG,strlen(ERRORMSG));
  } else {
    int n = atoi(argv[1]);
    sleep(n);
  }
  exit(0);
}
