int a_fetch_add(atomic_int *ptr, int value) {
    return atomic_fetch_add(ptr, value);
}