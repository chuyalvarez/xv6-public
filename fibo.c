#include "types.h"
#include "stat.h"
#include "user.h"


  int main(int argc,char*argv[]){

    uint n= 0, c, next= 0, first= 0, second= 1, j;
    uint slp = 65535;
    int priority;


    n = atoi(argv[1]);

    priority = atoi(argv[2]);
    set_priority(priority);

    for (c= 0; c< n; c++){
      if (c<= 1)
      next = c;
    else{
      next = first+ second;
      first = second;
      second = next;
    }

    //Busy for awhile
    for (j= 0; j< n; j++){

      while (slp){
        slp--;
      };

      slp = 65535;
      }
    }

    printf(1,"fibo[%d] = %d\n", n, next);

  exit();
  }
