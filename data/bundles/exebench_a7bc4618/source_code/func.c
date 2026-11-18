#include <stdio.h>

#include <stdlib.h>

#include <stdint.h>

#include <ctype.h>

#include <string.h>

#include <stdarg.h>

void remove_line_ending(char *text, char ending) {
  text = strrchr(text, ending);
  if(text)
    *text = 0;
}
