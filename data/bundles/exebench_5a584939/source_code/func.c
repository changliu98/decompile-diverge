#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int path_source_set(int *cfg_flag, int value) {
 *cfg_flag &= ~((0x04 | 0x02) | 0x08 );
 *cfg_flag |= (value & ((0x04 | 0x02) | 0x08 ));
 return *cfg_flag;
}
