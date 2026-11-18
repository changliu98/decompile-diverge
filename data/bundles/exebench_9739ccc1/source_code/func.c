#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdarg.h>

#include <unistd.h>

#include <signal.h>

#include <fcntl.h>

#include <termios.h>

void set_stimulus (unsigned char *dst, char *p)
{
 for (; *p; ++p)
  if (*p>='0' && *p<='7')
   *dst &= ~(1 << (*p-'0'));
}
