void sync_set_bit(int nr, volatile void *addr) {
    __asm__ __volatile__("lock bts %1, (%0)"
                         : 
                         : "r" (addr), "r" (nr)
                         : "memory");
}