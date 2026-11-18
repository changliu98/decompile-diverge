#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <sys/select.h>

#include <sys/socket.h>

#include <sys/wait.h>

#include <sys/un.h>

#include <sys/time.h>

#include <sys/ioctl.h>

#include <netinet/in.h>

static void set_page_data(int potval, char *buf)
{
 unsigned int word, *wordp;
 int len, blen;

 wordp = (unsigned int *)buf;
 word = potval;
 wordp[0] = word;

}
