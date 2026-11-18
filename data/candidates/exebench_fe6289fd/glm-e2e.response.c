long xchg8(long *ptr, long new_val) {
    long old_val = new_val;
    __asm__ volatile (
        "xchg %0, (%1)"
        : "+r" (old_val)
        : "r" (ptr)
    );
    return old_val;
}