void atomic_and(volatile unsigned long *ptr, unsigned long value) {
    unsigned long expected = *ptr;
    unsigned long desired;
    
    do {
        desired = expected & value;
    } while (!__sync_bool_compare_and_swap(ptr, expected, desired) && (expected = *ptr));
}