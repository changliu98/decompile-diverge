int atomicDecrement(_Atomic int *ptr) {
    return atomic_fetch_sub(ptr, 1) - 1;
}