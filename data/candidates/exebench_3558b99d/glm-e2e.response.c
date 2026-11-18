long ff_atomic_dec_long(long *ptr) {
    return __sync_fetch_and_sub(ptr, 1);
}