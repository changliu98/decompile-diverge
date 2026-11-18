long atomic_fetch_add(long *ptr, long value) {
    long old = *ptr;
    *ptr += value;
    return old;
}