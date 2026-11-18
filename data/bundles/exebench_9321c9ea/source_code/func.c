#include <stdint.h>

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <pthread.h>

static int sha256_init_hash(unsigned int *ret_digest_len)
{
 *ret_digest_len = 32;

 return 0;
}
