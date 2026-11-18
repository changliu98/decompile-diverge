int sync_test_and_set_bit(int nr, volatile unsigned long *addr) {
    int oldbit;
    __asm__ __volatile__(
        "lock bts %2, (%1)\n\t"
        "sbb %0, %0"
        : "=r" (oldbit)
        : "r" (addr), "r" (nr)
        : "memory", "cc"
    );
    return oldbit;
}