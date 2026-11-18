long AddUintptr(long *ptr, long val) {
#if defined(__x86_64__)
    long ret = __atomic_fetch_add(ptr, val, __ATOMIC_RELAXED);
#else
    long ret = *ptr;
    __atomic_add_32(ptr, val, &ret, __ATOMIC_RELAXED);
#endif
    return ret + val;
}