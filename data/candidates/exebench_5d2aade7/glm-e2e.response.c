long atomic_fetch_and(long *ptr, long value) {
    long old_val = *ptr;
    *ptr = old_val & value;
    return old_val;
}