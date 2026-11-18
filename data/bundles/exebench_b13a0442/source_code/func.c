#include <stdio.h>

#include <stdlib.h>

void strrev(char* s){
 int i,j;
 char c;

 for(i = 0 ; s[i] != '\0' ; i++);
 i--;
 for(j = 0 ;j<i ; i--,j++){
  c = s[i];
  s[i] = s[j];
  s[j] = c;
 }
}
