#include "types.h"
 #include "stat.h"
 #include "user.h"
 #include "fcntl.h"

 #define passwdFile "/passwd"
 #define maxLength 100

 char * itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int contains(char *str, char *pattern){
   int i=0,j=0;
   int sizeStr = strlen(str);
   int sizePattern = strlen(pattern);

   while(i<sizePattern && j<sizeStr && pattern[i] != str[j]){
     j++;
   }
   if (j==sizeStr){
     return 0;
   }
   while(i<sizePattern && j<sizeStr && pattern[i] == str[j]){
     i++;
     j++;
   }
   if(i== sizePattern) {
     return 1;
   }else{
     return 0;
   }
 }

 int readLine(int fd, char *buf, int size){
   int i=0, n=0;
   char c;
   while(read(fd, &c, 1)>0){
     n++;
     if(c!='\n'){
       buf[i] = c;
       i++;
     } else  break;
   }
   buf[i] = '\0';
   return n;
 }

 int getid(char *record){
   int i=0;
   int j=0;
   char id[5];
   while (record[i]!=':'){
     i++;
   }
  i++;
  while (record[i]!=':'){
    id[j]=record[i];
    i++;
    j++;
  }
  return atoi(id)+1;
 }

 int main(int argc, char *argv[])
 {
   int fd;
   char record[maxLength];
   char id[5];
   int n;
   int uid=0;
   char newuser[maxLength];
   char readbuf[1024];
   int pid,wpid;
   char *shArgv[] = {"sh",0};

   if(argc != 3){
     printf(2, "Usage adduser newUser newPassword\n");
     return 1;
   }

   fd = open(passwdFile,O_RDWR);

   while((n = readLine(fd,record,sizeof(record)))>0){
     if(contains(record,argv[1])){
       printf(1,"inavlid username\n" );
       close(fd);
       exit();
     }
     uid=getid(record);
   }
   itoa(uid,id,10);

   strcpy(newuser,argv[1]);
   strcpy(newuser + strlen(newuser),":");
   strcpy(newuser + strlen(newuser),id);
   strcpy(newuser + strlen(newuser),":");
   strcpy(newuser + strlen(newuser),argv[2]);
   strcpy(newuser + strlen(newuser),":\n");

   read( fd, readbuf, sizeof(readbuf) );
  if( write(fd, newuser, strlen(newuser))>0){
      printf(1,"Welcome %s with pass %s\n",argv[1],argv[2] );
      pid = fork();
      if(pid < 0){
        printf(1, "login: fork failed\n");
        exit();
      }
      if(pid == 0){
        exec("sh", shArgv);
        printf(1, "init: exec sh failed\n");
        exit();
      }
      while((wpid=wait()) >= 0 && wpid != pid){
        printf(1, "zombie!\n");
      }
  }

  close(fd);
   exit();
 }
