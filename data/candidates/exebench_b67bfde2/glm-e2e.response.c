int wdl_atomic_incr(int* ptr) {
    int old_value;
    int new_value;
    
    // 'lock xadd' atomically adds the value of %eax (1) to *ptr,
    // and stores the original value of *ptr into %eax.
    __asm__ __volatile__(
        "lock xadd %0, (%1)"
        : "=a" (old_value)
        : "a" (1), "c" (ptr)
        : "memory"
    );
    
    // The assembly adds 1 to the returned old value to get the new value
    new_value = old_value + 1;
    
    return new_value;
}