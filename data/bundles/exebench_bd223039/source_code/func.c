#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

void clearMarker(char * s, char marker)
{
 char * pos;

 if ((pos = strchr(s, marker)) != NULL) {
  *pos = '\0';
 }
}
