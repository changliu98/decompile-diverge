#include <stdlib.h>

#include <stdint.h>

#include <limits.h>

#include <errno.h>

inline static int _safe_calloc_check_add(size_t a, size_t b, size_t *res)
{
 size_t tmp;

 return !__builtin_add_overflow(a, b, res ? res : &tmp);
}
