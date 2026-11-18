void atomic_inc(_Atomic int *ptr) {
    atomic_fetch_add(ptr, 1);
}