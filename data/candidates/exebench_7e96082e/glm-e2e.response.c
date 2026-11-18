void atomic_dec(int *ptr) {
    __asm__ __volatile__(
        "lock decl (%0)"
        : 
        : "r" (ptr)
        : "memory"
    );
}