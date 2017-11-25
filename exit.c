#include "types.h"
#include "stat.h"
#include "user.h"

char *argv[] = { "login", 0 };

int main(void){
  //kill(getparentpid());
  exec("login", argv);
  exit();
}
