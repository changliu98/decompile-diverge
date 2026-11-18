void sync_clear_bit(int nr, volatile unsigned long *addr) {
    // Atomically clears the 'nr'-th bit in the memory pointed to by 'addr'.
    // This is equivalent to the GCC __sync_and_and_fetch intrinsic, 
    // or standard C11 atomics.
    atomic_fetch_and(addr, ~(1UL << nr));
}