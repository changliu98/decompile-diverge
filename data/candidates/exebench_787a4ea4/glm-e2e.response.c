int atomic_add(int *ptr, int value) {
    return atomic_fetch_add(ptr, value);
}