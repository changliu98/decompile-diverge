static inline int _hclib_atomic_dec_relaxed(volatile int *target) {
    return __sync_sub_and_fetch(target, 1);
}