long ihk_atomic_add_long_return(long *ptr, long value) {
    long old_value;
    
    // 'lock xadd' atomically adds 'value' to '*ptr' and returns the old value of '*ptr'
    old_value = __sync_fetch_and_add(ptr, value);
    
    // The function is expected to return the NEW value, so we add 'value' to the returned old value
    return old_value + value;
}