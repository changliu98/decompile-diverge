int test_and_set(int *lock) {
    int old = *lock;
    *lock = 1;
    return old;
}