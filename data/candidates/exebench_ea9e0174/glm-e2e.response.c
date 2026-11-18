int atomic_add(_Atomic int *ptr, int value) {
    return atomic_fetch_add(ptr, value);
}