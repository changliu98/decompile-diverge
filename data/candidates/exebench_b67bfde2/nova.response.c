int wdl_atomic_incr(int *ptr) {
    int val = ++*ptr;
    return val + 1;
}