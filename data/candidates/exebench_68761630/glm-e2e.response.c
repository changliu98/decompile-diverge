void a_or(_Atomic int *ptr, int val) {
    atomic_fetch_or(ptr, val);
}