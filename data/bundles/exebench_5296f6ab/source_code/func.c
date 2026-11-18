#include <assert.h> /* assert() */

#include <ctype.h>

#include <stddef.h> /* NULL size_t */

#include <stdio.h>

#include <stdlib.h>

#include <string.h> /* memset() strcmp() strcpy() strlen() */

static void
charset_remove(char buffer[], char value)
{
 char *l = buffer;
 const char *r = buffer;
 while(*r != '\0')
 {
  if(*r != value)
  {
   *l++ = *r;
  }
  r++;
 }
 *l++ = '\0';
}
