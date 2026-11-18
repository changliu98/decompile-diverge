int atomicIncrement(_Atomic int* ptr) {
    return atomic_fetch_add(ptr, 1) + 1;
}