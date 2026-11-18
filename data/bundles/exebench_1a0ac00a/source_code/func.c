#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

#include <stdarg.h>

void agrega(int *head, int *tail, int i, int *ll){
 if(*head==-1){
  *head=i;
  *tail=i;
 }else{
  ll[*tail]=i;
  *tail=i;
 }
 ll[*tail]=-1;
 return;
}
