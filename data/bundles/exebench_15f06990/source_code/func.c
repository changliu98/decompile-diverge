
static inline void sync_unlock(int* ptr) {
    return __sync_lock_release(ptr);
}
