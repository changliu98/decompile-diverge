#include <errno.h>

#include <stdbool.h>

#include <stdio.h>

#include <string.h>

#include <sys/uio.h>

#include <syslog.h>

#include <unistd.h>

static inline void closep(int *fd) {
  if (*fd >= 0)
    close(*fd);
  *fd = -1;
}
