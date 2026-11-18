uintptr_t AddUintptr(uintptr_t *ptr, uintptr_t value) {
    return __sync_fetch_and_add(ptr, value);
}