#include <ctype.h>

#include <errno.h>

#include <fcntl.h>

#include <pwd.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <signal.h>

#include <unistd.h>

#include <time.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <sys/stat.h>

#include <sys/wait.h>

static char * envstring(char *str){
 char *s;
 for(s = str; *s; s++){
  if(*s == '-')
   *s = '_';
  else if((*s >= 'a') && (*s <= 'z'))
   *s -= 'a' - 'A';
  else if((*s < 'A') || (*s > 'Z')){
   *str = 0;
   break;
  }
 }

 return str;
}
