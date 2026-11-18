void atomic_or(uint64_t *ptr, uint64_t value) {
    uint64_t expected;
    uint64_t desired;
    
    // Read the initial value of the pointer
    expected = *ptr;
    
    // Retry loop for atomic compare-and-swap
    while (1) {
        desired = expected | value;
        
        // Atomically compare and exchange
        // If *ptr == expected, then *ptr = desired and ZF is set (returns true)
        // Else expected = *ptr and ZF is cleared (returns false)
        if (__sync_bool_compare_and_swap(ptr, expected, desired)) {
            break;
        }
    }
}