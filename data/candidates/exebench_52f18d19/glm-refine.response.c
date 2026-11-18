int atomicIncrement(volatile int *var) {
    // __atomic_fetch_add returns the previous value, so we add 1 to get the new value.
    // This perfectly matches the semantics of _InterlockedIncrement.
    return __atomic_fetch_add(var, 1, __ATOMIC_SEQ_CST) + 1;
}