#include <stdint.h>

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <assert.h>

#include <string.h>

static int murmur3_init_hash(unsigned int *ret_digest_len)
{
 *ret_digest_len = 16;
 return 0;
}
