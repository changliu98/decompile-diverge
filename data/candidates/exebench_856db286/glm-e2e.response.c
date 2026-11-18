int _hclib_atomic_dec_relaxed(int32_t *ptr) {
    // The 'lock xadd' instruction atomically adds the value in %eax (-1) to *ptr
    // and stores the original value of *ptr into %eax.
    // The subsequent 'sub $0x1, %eax' adjusts the return value to be the new decremented value.
    int old_val = __sync_fetch_and_add(ptr, -1);
    return old_val - 1;
}