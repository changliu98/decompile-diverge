int test_and_change_bit(int nr, volatile unsigned long *addr) {
    int oldbit;
    
    // The 'btc' instruction (Bit Test and Complement) tests the bit at position 'nr' 
    // in the memory at 'addr', stores the original bit value in the Carry Flag (CF), 
    // and then flips (complements) the bit in memory.
    // The 'sbb %eax, %eax' instruction subtracts with borrow. If CF was 1, it 
    // subtracts 1 from 0 resulting in -1 (0xFFFFFFFF). If CF was 0, it results in 0.
    
    __asm__ volatile (
        "btc %1, %2\n\t"
        "sbb %0, %0"
        : "=r" (oldbit)
        : "r" (nr), "m" (*addr)
        : "memory", "cc"
    );
    
    return oldbit;
}