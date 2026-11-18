int _hclib_atomic_dec_release(int *ptr) {
    // The 'lock xadd' instruction atomically adds the value in %eax (-1) to *ptr,
    // and stores the original value of *ptr into %eax.
    // The 'sub $0x1, %eax' then decrements this original value to return the new value.
    return __sync_add_and_fetch(ptr, -1);
}