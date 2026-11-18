bool a_swap(int *ptr, int new_val) {
    int expected;
    do {
        expected = *ptr;
    } while (!__sync_bool_compare_and_swap(ptr, expected, new_val));
    
    return expected;
}