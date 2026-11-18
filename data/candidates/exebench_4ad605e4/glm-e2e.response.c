int atmc_fetch_and_add(int* ptr, int value) {
    return __sync_fetch_and_add(ptr, value);
}