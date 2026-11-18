int test_and_clear_bit(int nr, volatile unsigned long *addr) {
    int oldbit;
    __asm__ __volatile__(
        "btr %1, (%2)\n\t"
        "sbb %0, %0"
        : "=r" (oldbit)
        : "r" (nr), "r" (addr)
        : "memory"
    );
    return oldbit;
}