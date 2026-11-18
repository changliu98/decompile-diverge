#include <stdio.h>

#include <string.h>

#include <stdlib.h>

static void SHUF(unsigned char b[16], unsigned char b2[16]) {
 b2[0] = b[8]; b2[1] = b[11]; b2[2] = b[12]; b2[3] = b[15];
 b2[4] = b[2]; b2[5] = b[1]; b2[6] = b[6]; b2[7] = b[5];
 b2[8] = b[10]; b2[9] = b[9]; b2[10] = b[14]; b2[11] = b[13];
 b2[12] = b[0]; b2[13] = b[7]; b2[14] = b[4]; b2[15] = b[3];
}
