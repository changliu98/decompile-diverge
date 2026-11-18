int test_and_set_bit(int nr, volatile unsigned long *addr) {
    return atomic_fetch_or_explicit((atomic_ulong *)addr, 1UL << nr, memory_order_seq_cst) >> nr & 1;
}