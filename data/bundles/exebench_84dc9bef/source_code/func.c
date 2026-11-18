#include <stdio.h>

#include <limits.h>

#include <time.h>

#include <math.h>

void trim(char *str){
 int i=0;
 for(;;){
  if(str[i]=='\0'){
   str[i-1]='\0';
   return;
  }
  i++;
 }
}
