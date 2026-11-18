int test_and_set_bit(int nr, unsigned long *addr) {
    int oldbit;
    asm volatile (
        "bts %2, (%1)"
        : "=&a" (oldbit)
        : "d" (addr), "c" (nr)
        : "memory"
    );
    return oldbit;
}