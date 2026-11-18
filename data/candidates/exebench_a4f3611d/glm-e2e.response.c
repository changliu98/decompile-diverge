int sync_test_and_change_bit(int nr, volatile unsigned long *addr) {
    int oldbit;
    
    // lock btc performs: oldbit = *addr & (1 << nr); *addr ^= (1 << nr);
    // sbb %eax, %eax sets %eax to -1 if the Carry Flag (CF) was set, 0 otherwise.
    // This effectively returns the old bit value as 0 or -1 (which evaluates to 0 or 1 in boolean logic).
    __asm__ volatile (
        "lock btc %1, %2\n\t"
        "sbb %0, %0"
        : "=r" (oldbit)
        : "r" (nr), "m" (*addr)
        : "memory"
    );
    
    return oldbit;
}