bool test_and_change_bit(long nr, unsigned long *addr) {
    bool old_bit;
    
    // The 'btc' instruction (Bit Test and Complement) tests the bit at position 'nr' 
    // in the memory pointed to by 'addr', stores its original value in the CF (Carry Flag),
    // and then flips (complements) the bit in memory.
    // 'setb' captures the Carry Flag into 'old_bit'.
    __asm__ volatile (
        "btc %1, %2\n\t"
        "setb %0"
        : "=q" (old_bit)
        : "r" (nr), "m" (*addr)
        : "cc", "memory"
    );
    
    return old_bit;
}