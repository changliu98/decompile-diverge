void set_bit(int bit, unsigned long *addr) {
    __asm__ ("bts %1, (%0)" : : "r"(addr), "r"(bit) : "memory");
}