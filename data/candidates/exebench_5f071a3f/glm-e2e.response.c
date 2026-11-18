bool StoreUintptr(uintptr_t *ptr, uintptr_t new_value) {
    uintptr_t expected = *ptr;
    while (true) {
        // Atomically compare and exchange:
        // If *ptr == expected, then *ptr = new_value and return true.
        // Otherwise, expected = *ptr and return false.
        if (__sync_bool_compare_and_swap(ptr, expected, new_value)) {
            return true;
        }
        // If the CAS failed, update expected with the current value of *ptr and retry
        expected = *ptr;
    }
}