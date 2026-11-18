#include <stddef.h>

static inline void atomic_or(volatile size_t* x,size_t val) {

  __sync_or_and_fetch(x,val);







}
