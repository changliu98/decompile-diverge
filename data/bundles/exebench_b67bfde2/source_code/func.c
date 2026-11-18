
static int wdl_atomic_incr(int *v) { return __sync_add_and_fetch(v,1); }
