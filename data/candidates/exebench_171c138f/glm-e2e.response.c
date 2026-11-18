int32_t atomic_add32_ret(int32_t* ptr) {
    int32_t val = 1;
    // lock xadd %eax, (%rcx) atomically adds val to *ptr 
    // and stores the original value of *ptr into val.
    __asm__ __volatile__(
        "lock xadd %0, (%1)"
        : "+a" (val)
        : "c" (ptr)
        : "memory"
    );
    return val;
}