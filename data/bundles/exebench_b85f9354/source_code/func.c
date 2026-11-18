#include <stddef.h>

#include <stdio.h>

void calculate_crc(char *crc, char newval)
{
# 103 "utils.c"
  *crc ^= newval;
}
