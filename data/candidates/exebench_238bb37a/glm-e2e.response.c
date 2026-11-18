long incr(long *ptr, long value) {
    long old_value = *ptr;
    long new_value = old_value + value;
    *ptr = new_value;
    return old_value;
}