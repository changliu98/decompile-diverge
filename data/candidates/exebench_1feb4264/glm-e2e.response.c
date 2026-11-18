int atomicCompareAndSwap(int* ptr, int expected, int desired) {
    return atomic_compare_exchange_strong(ptr, &expected, desired);
}