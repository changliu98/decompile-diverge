#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <sys/select.h>

#include <fcntl.h>

#include <netinet/ip.h>

#include <netinet/in.h>

#include <string.h>

#include <errno.h>

#include <sys/time.h>

#include <signal.h>

void SwitchToChar(char* str,unsigned char data)
{
 if(data/16>=10){
 *str = 'A'+data/16-10;
 }else{
 *str = '0'+data/16;
 }

  if(data%16>=10){
    *(str+1) = 'A'+data%16-10;
  }else{
   *(str+1) = '0'+data%16;
  }
}
