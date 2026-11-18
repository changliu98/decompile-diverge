int xchg(_Atomic int *addr, int new_val) {
    return atomic_exchange(addr, new_val);
}