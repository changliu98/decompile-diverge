int atomic32_decrement(int* ptr) {
    int dec = -1;
    // lock xadd %eax, (%rcx) atomically adds the value of %eax (-1) to *ptr
    // and stores the original value of *ptr into %eax.
    int old_val = __sync_fetch_and_add(ptr, dec);
    // The assembly subtracts 1 from the returned old value to get the new value
    return old_val - 1;
}