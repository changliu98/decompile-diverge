#include <stdio.h>

#include <stdarg.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#include <assert.h>

#include <unistd.h>

static void lemon_strcpy(char *dest, const char *src){
  while( (*(dest++) = *(src++))!=0 ){}
}
