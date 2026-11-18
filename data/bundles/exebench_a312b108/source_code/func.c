#include <stdint.h>

static inline intptr_t atomic_fetch_xor(intptr_t *object, intptr_t operand) { intptr_t ret; ret = *object; *object = *object ^ operand; return ret; }
