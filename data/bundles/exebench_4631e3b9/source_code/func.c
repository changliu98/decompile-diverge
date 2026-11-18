#include <stdio.h>

#include <string.h>

int c_decrypt(char *text){
 int c;
 while(*text != '\0') {

  c = *text-13;
  if(c <= 0){
   c += 256;
  }
  *text = c;
  text++;

 }

 return 0;
}
