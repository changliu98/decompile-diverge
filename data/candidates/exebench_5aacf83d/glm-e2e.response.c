int a_swap(_Atomic int *ptr, int new_val) {
    return atomic_exchange(ptr, new_val);
}