int func0(int *lock) {
    int val = __atomic_fetch_add(lock, 1, __ATOMIC_RELAXED);
    return val + 1;
}