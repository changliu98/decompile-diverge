#include <stdio.h>

#include <ctype.h>

#include <string.h>

#include <limits.h>

#include <stdbool.h>

#include <errno.h>

#include <stdlib.h>

#include <stdarg.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <sys/mman.h>

#include <fcntl.h>

#include <unistd.h>

#include <elf.h>

static void get_payload_info(char *bzimage, int *offset, int *size)
{
 unsigned int system_offset;
 unsigned char setup_sectors;

 setup_sectors = bzimage[0x1f1] + 1;
 system_offset = setup_sectors * 512;
 *offset = system_offset + *((int*)&bzimage[0x248]);
 *size = *((int*)&bzimage[0x24c]);
}
