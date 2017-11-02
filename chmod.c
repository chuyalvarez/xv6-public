#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3){
    printf(2, "Usage: chmod\n");
    exit();
  }

  for(i = 0;i < 3;i++) permissions[i] = argv[1][i] - '0';


  permission[3] = 0;
  if(chmod(argv[1], argv[2]) < 0)
    printf(2, "link %s %s: failed\n", argv[1], argv[2]);
  exit();
}
