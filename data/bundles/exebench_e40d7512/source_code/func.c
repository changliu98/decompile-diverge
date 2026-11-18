#include <sys/cdefs.h>

#include <sys/param.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <sys/file.h>

#include <pwd.h>

#include <unistd.h>

#include <sys/uio.h>

#include <signal.h>

#include <termios.h>

#include <syslog.h>

#include <fcntl.h>

#include <dirent.h>

#include <errno.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include <stdarg.h>

static char *
scnline(int key, char *p, int c)
{
 int scnwidth;

 for (scnwidth = 8; --scnwidth;) {
  key <<= 1;
  *p++ = key & 0200 ? c : ' ';
 }
 return (p);
}
