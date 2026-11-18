int32_t atomic32_increment(int32_t *value) {
    int32_t old_value;
    // 'lock xadd' atomically adds 1 to *value and returns the previous value
    // __asm__ __volatile__("lock xadd %1, (%2)" : "=a"(old_value) : "r"(1), "r"(value) : "memory");
    
    // Alternatively, using standard C11 atomics:
    // old_value = __atomic_fetch_add(value, 1, __ATOMIC_SEQ_CST);
    
    return old_value + 1;
}