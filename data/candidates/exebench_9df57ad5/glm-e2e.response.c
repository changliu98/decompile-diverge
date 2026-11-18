void a_store(_Atomic int *ptr, int value) {
    atomic_store_explicit(ptr, value, memory_order_release);
}