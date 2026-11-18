void atomic_add(int value, atomic_int *ptr) {
    atomic_fetch_add(ptr, value);
}