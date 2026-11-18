int atomic_sub(_Atomic int *ptr, int val) {
    return atomic_fetch_sub(ptr, val);
}