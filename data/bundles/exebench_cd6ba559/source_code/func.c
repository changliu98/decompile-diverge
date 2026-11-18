#include <stdint.h>

uintptr_t
AddUintptr (uintptr_t *val, uintptr_t delta)
{
  return __sync_add_and_fetch (val, delta);
}
